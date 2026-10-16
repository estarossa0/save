---
name: repo-sync
description: Use when syncing changes from the secondary GitHub org (permianlabs-internal) to the main orgs (metastreet-labs or usdai-foundation) — re-authors the fork's main to the dev (Vercel blocks non-member authors), pushes it as a sync branch to both repos, opens a PR, triggers a security review, and merges with a merge commit
disable-model-invocation: false
---

# Repo Sync

## Overview

Non-technical team members work in an isolated GitHub org (`permianlabs-internal`). Their repos are clones (not forks) of repos in the main orgs (`metastreet-labs` or `usdai-foundation`). This skill syncs their work back to the main org via a reviewed PR.

**REQUIRED:** Load `ai-team-oversight` skill before proceeding — the PR created by this workflow must pass the security review checklist.

## How the two repos stay in sync

Both repos share git history (since 2026-10-16 for `usdai-landing`):

- **main → fork** is automatic: `.github/workflows/sync-to-fork.yml` merges the main repo's `main` into the fork's `main` on every push. On a conflict it opens a `sync-conflict-<sha>` PR on the fork for a dev to resolve.
- **fork → main** is this skill: the fork's `main` is pushed to the main repo as a sync branch, reviewed, and merged with a **merge commit**.

**Never squash a sync PR, and never rebase it on GitHub.** That rewrites the fork's commits on one side only and breaks the shared history; the next main → fork run would then conflict on every replay. Both repos' settings allow merge commits only — keep it that way.

**Authorship:** Vercel blocks any deployment whose commit author is not a member of the Vercel team, and the fork's contributors (e.g. `chubot5000`) are not members. So Step 5 rewrites every fork commit to be authored by the dev running the skill, with the original author as `Co-Authored-By`, and force-pushes that rewritten line back to the fork's `main` as well. Both repos then share the rewritten commits, so the shared-history invariant holds. This is the only place history is rewritten.

## Workflow

### Step 1: Discover matching repos

Store each org's repo list in arrays to avoid garbled output from combined subshells:

```bash
SECONDARY=($(gh repo list permianlabs-internal --limit 100 --json name -q '.[].name'))
MAIN1=($(gh repo list metastreet-labs --limit 100 --json name -q '.[].name'))
MAIN2=($(gh repo list usdai-foundation --limit 100 --json name -q '.[].name'))

for repo in "${SECONDARY[@]}"; do
  if printf '%s\n' "${MAIN1[@]}" | grep -qx "$repo"; then
    echo "$repo → metastreet-labs/$repo"
  elif printf '%s\n' "${MAIN2[@]}" | grep -qx "$repo"; then
    echo "$repo → usdai-foundation/$repo"
  fi
done
```

Parse the output to build the list of matches.

### Step 2: Prompt the user

**If 0 matches:** Report that no matching repos were found and stop.

**If 1 match:** Skip `AskUserQuestion` (it requires ≥2 options). Instead, present the single match and use `AskUserQuestion` as a yes/no confirmation:

```
AskUserQuestion({
  questions: [{
    question: "Only one matching repo found: <repo-name> → <main-org>/<repo-name>. Proceed with sync?",
    header: "Confirm",
    options: [
      { label: "Yes, sync it", description: "Push fork main as a sync branch and open a PR" },
      { label: "No, cancel", description: "Stop the repo-sync workflow" }
    ],
    multiSelect: false
  }]
})
```

**If 2+ matches:** Use `AskUserQuestion` to present the matched repos as selectable options:

```
AskUserQuestion({
  questions: [{
    question: "Which repo do you want to sync?",
    header: "Repo",
    options: [
      { label: "repo-name-a", description: "→ metastreet-labs/repo-name-a" },
      { label: "repo-name-b", description: "→ usdai-foundation/repo-name-b" }
    ],
    multiSelect: false
  }]
})
```

Do NOT proceed without user confirmation or selection.

### Step 3: Set up local clone

Use the session scratchpad directory (not `/tmp`). If `<scratchpad>/repo-sync/<repo-name>` already exists, reuse it; otherwise clone the main repo:

```bash
git clone https://github.com/<main-org>/<repo-name> <scratchpad>/repo-sync/<repo-name>
cd <scratchpad>/repo-sync/<repo-name>
git remote set-url fork https://github.com/permianlabs-internal/<repo-name> 2>/dev/null \
  || git remote add fork https://github.com/permianlabs-internal/<repo-name>
git fetch origin <main-default-branch>
git fetch fork <fork-default-branch>
```

### Step 4: Pre-flight

```bash
# 1. Shared history: main must be an ancestor of the fork's main.
git merge-base --is-ancestor origin/<main-default-branch> fork/<fork-default-branch> \
  && echo "ok: fork is ahead of main" \
  || echo "STOP: fork main is not a descendant of main"

# 2. Anything to sync?
git rev-list --count origin/<main-default-branch>..fork/<fork-default-branch>
```

- **If check 1 fails:** the main → fork Action fell behind, or a `sync-conflict-*` PR is open on the fork. Look for that PR (`gh pr list --repo permianlabs-internal/<repo-name> --search "sync-conflict"`) and the latest `sync-to-fork.yml` run on the main repo. Fix that first; do not cherry-pick around it. If the repo has never been re-baselined, see **Legacy repos** below.
- **If check 2 is 0:** report that there is nothing to sync and stop.

### Step 5: Re-author and push the sync branch

1. Pick the branch name. Check for an existing open sync PR first:
   ```bash
   gh pr list --repo <main-org>/<repo-name> --state open --search "head:repo-sync-" --json number,headRefName
   ```
   - **Open sync PR exists:** reuse its branch name and skip Step 6; the PR auto-updates.
   - **No open PR:** `BRANCH="repo-sync-$(date +%Y-%m-%d)"` (append `-2`, `-3` if taken).

2. Build the re-authored line on top of main. The rebase linearizes the fork's history and drops any commit whose patch is already on main (e.g. a duplicate left by a contributor's merge-pull after an earlier rewrite):
   ```bash
   FORK_SHA=$(git rev-parse fork/<fork-default-branch>)
   NAME=$(git config user.name); EMAIL=$(git config user.email)
   git checkout -B "$BRANCH" "$FORK_SHA"
   git rebase origin/<main-default-branch> \
     --exec 'A="$(git log -1 --format="%an <%ae>")"; git commit --amend --no-edit --author="'"$NAME <$EMAIL>"'" --trailer "Co-Authored-By: $A"'
   git log --format='%h %an | %(trailers:key=Co-Authored-By,valueonly)' origin/<main-default-branch>..HEAD
   ```
   Every commit must now show the dev as author and the original author in the trailer. If the rebase conflicts, the main → fork Action is behind (Step 4 should have caught it); abort and fix that first.

3. Push the same commits to both repos. The fork push uses a lease on the SHA fetched in step 2, so a contributor pushing in between fails the push instead of losing work:
   ```bash
   git push origin "$BRANCH"                              # new PR: plain push; existing PR: add --force-with-lease
   git push fork "HEAD:refs/heads/<fork-default-branch>" --force-with-lease="<fork-default-branch>:$FORK_SHA"
   ```
   If the fork push is rejected, re-fetch `fork/<fork-default-branch>` and repeat from step 2.

After this, fork `main` and the sync branch point at the same commit. Fork contributors whose local clone still has the pre-rewrite commits should `git pull --rebase`; a merge-pull reintroduces the old commits, which the next sync's rebase drops again.

### Step 6: Open the PR (new sync only)

```bash
gh pr create \
  --repo <main-org>/<repo-name> \
  --base <main-default-branch> \
  --head "$BRANCH" \
  --title "Sync from permianlabs-internal — $BRANCH" \
  --body ""
```

### Step 7: Verify the branch

In the local clone, check out the sync branch and run what the repo offers (typecheck, lint, tests). Compare lint error counts against `origin/<main-default-branch>` rather than demanding zero; report only new failures.

### Step 8: Security review

1. Invoke `/security-review` on the PR diff (`origin/<main-default-branch>...<sync-branch>`).
2. Verify every item in the `ai-team-oversight` Review Checklist against the diff.
3. List every new or changed external URL for the dev to verify manually.
4. Report findings to the user with clear pass/fail for each checklist item.

### Step 9: Update PR description with review results

Set the PR description to just:

```bash
gh pr edit <PR-NUMBER> --repo <main-org>/<repo-name> --body "$(cat <<'BODY'
## Summary
<bullet points describing the actual code changes>

<one line: sync base = fork <sha>; verification results; dependency changes or "none">

## Risks
<identified risks, new external URLs to verify, overlapping open PRs, or "None">

## Security Review
<full output from /security-review>
BODY
)"
```

No filler text like "syncing from X", "source: X", or "review required". Just the changes and the review output.

### Step 10: Re-review (if requested)

If the dev makes fixes and asks for a re-review:

1. Run `/security-review` again on the same PR.
2. Verify the `ai-team-oversight` checklist again.
3. **Replace** the entire PR description with the updated summary and review output — do not stack multiple review sections.

### Step 11: Merge

**Always use the `gh` CLI**, always with a merge commit:

```bash
gh pr merge <PR-NUMBER> --repo <main-org>/<repo-name> --merge --delete-branch
```

Only add `--admin` when the user explicitly asks to bypass branch rules. The GitHub MCP `merge_pull_request` tool returns 404 on these repos; do not use it.

### Step 12: Confirm the round trip

After the merge, the main repo's `sync-to-fork.yml` run should fast-forward the fork:

```bash
gh run list --repo <main-org>/<repo-name> --workflow sync-to-fork.yml --limit 1
git fetch origin <main-default-branch>; git fetch fork <fork-default-branch>
git rev-parse origin/<main-default-branch> fork/<fork-default-branch>   # must match
```

If the run failed with a conflict, a `sync-conflict-<sha>` PR is waiting on the fork.

## Dev fixes on a sync branch

If the dev needs to change something before merging, commit on top of the sync branch in the main repo and push. The merge commit carries those fixes to main, and the Action then merges them into the fork. Do not rewrite the re-authored commits underneath: the fork already has them.

## Legacy repos (not yet re-baselined)

A repo whose fork does not share history with main (Step 4 check 1 fails and there is no conflict PR) must be bootstrapped once before this flow works:

1. Sync the fork's pending commits one last time by cherry-picking them onto a branch from main (`git cherry-pick <main>..fork/<main>`), re-author each commit to the dev with the original author as `Co-Authored-By`, open and review the PR as above, and squash-merge it.
2. Verify `git diff origin/<main> fork/<main>` is empty, or that every remaining difference is one where main's version should win.
3. Tell the fork's contributors to push any in-flight work, then `git push fork origin/<main>:refs/heads/<main> --force`.
4. Set the main repo to merge commits only: `gh api -X PATCH repos/<main-org>/<repo-name> -F allow_merge_commit=true -F allow_squash_merge=false -F allow_rebase_merge=false`.
5. Make sure the repo's `sync-to-fork.yml` is the merge-based version (copy it from `metastreet-labs/usdai-landing`) and that the `FORK_SYNC_PAT` secret exists.

## Cleanup

After the PR is merged or closed, the scratchpad clone can be left for reuse or removed with `rmf -r <scratchpad>/repo-sync/<repo-name>`.
