---
name: repo-sync
description: Use when syncing changes from the secondary GitHub org (permianlabs-internal) to the main orgs (metastreet-labs or usdai-foundation) — fetches matching repos, creates a sync branch, opens a PR, and triggers a security review
disable-model-invocation: false
---

# Repo Sync

## Overview

Non-technical team members work in an isolated GitHub org (`permianlabs-internal`). Their repos are clones (not forks) of repos in the main orgs (`metastreet-labs` or `usdai-foundation`). This skill automates syncing their work back to the main org via a reviewed PR.

**REQUIRED:** Load `ai-team-oversight` skill before proceeding — the PR created by this workflow must pass the security review checklist.

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
      { label: "Yes, sync it", description: "Clone both repos, create sync branch, and open a PR" },
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

### Step 3: Check for existing open PR

Before cloning or creating anything, check if there's already an open sync PR for this repo:

```bash
gh pr list --repo <main-org>/<repo-name> --state open --head "repo-sync-" --json number,title,headRefName
```

- **If an open PR exists:** Ask the user whether to **update the existing PR** or **create a new one**.
  - If only 1 open PR: use yes/no confirmation (AskUserQuestion with 2 options).
  - If 2+ open PRs: let the user pick which one to update, or create new.
- **If no open PR:** Proceed to create a new sync branch and PR (Step 4).

### Step 4: Set up local clone

If `/tmp/repo-sync-<repo-name>/<repo-name>` already exists, reuse it — just fetch latest:

```bash
cd /tmp/repo-sync-<repo-name>/<repo-name>
git fetch --all
```

If it doesn't exist, clone the main repo only (no fork clone needed):

```bash
mkdir -p /tmp/repo-sync-<repo-name>
git clone https://github.com/<main-org>/<repo-name> /tmp/repo-sync-<repo-name>/<repo-name>
```

Then ensure the fork remote points to the GitHub URL (add or update):

```bash
cd /tmp/repo-sync-<repo-name>/<repo-name>
git remote set-url fork https://github.com/permianlabs-internal/<repo-name> 2>/dev/null || git remote add fork https://github.com/permianlabs-internal/<repo-name>
git fetch fork
```

### Step 5a: Update existing PR (if updating)

1. Checkout the existing sync branch and pull latest:
   ```bash
   git checkout <existing-branch-name>
   git pull origin <existing-branch-name>
   ```

2. Use `git cherry` to find commits not yet picked (marked with `+`), then cherry-pick only those:
   ```bash
   NEW_COMMITS=$(git cherry <existing-branch-name> fork/<fork-default-branch> | grep '^+' | awk '{print $2}')
   if [ -z "$NEW_COMMITS" ]; then
     echo "No new commits to sync"
   else
     git cherry-pick $NEW_COMMITS
   fi
   ```

3. Push (fast-forward — cherry-picks add on top):
   ```bash
   git push origin <existing-branch-name>
   ```

4. Skip PR creation — the existing PR auto-updates. Proceed to Step 6 (security review).

### Step 5b: Create new sync branch and PR (if creating new)

1. Checkout the main branch and create a new sync branch:
   ```bash
   git checkout <main-default-branch>
   git pull origin <main-default-branch>
   BRANCH_NAME="repo-sync-$(date +%Y-%m-%d)"
   git checkout -b "$BRANCH_NAME"
   ```

2. Cherry-pick all new commits from the fork:
   ```bash
   git cherry-pick <main-default-branch>..fork/<fork-default-branch>
   ```

3. Push the sync branch:
   ```bash
   git push origin "$BRANCH_NAME"
   ```

### Step 5c: Open a PR (only for new sync)

Create a PR from the sync branch to the main repo's default branch with an empty body initially:

```bash
gh pr create \
  --repo <main-org>/<repo-name> \
  --base <main-default-branch> \
  --head "$BRANCH_NAME" \
  --title "Sync from permianlabs-internal — $BRANCH_NAME" \
  --body ""
```

### Step 6: Security review

1. Invoke `/security-review` on the newly created PR.
2. Additionally, verify every item in the `ai-team-oversight` Review Checklist against the PR diff.
3. Report findings to the user with clear pass/fail for each checklist item.

### Step 7: Update PR description with review results

After the review is complete, set the PR description to just:
- **Summary** of the actual code changes (what was added/modified/removed)
- The full output of the `/security-review` skill

```bash
gh pr edit <PR-NUMBER> --repo <main-org>/<repo-name> --body "$(cat <<'EOF'
## Summary
<bullet points describing the actual code changes>

## Risks
<identified risks or "None">

## Security Review
<full output from /security-review>
EOF
)"
```

No filler text like "syncing from X", "source: X", or "review required". Just the changes and the review output.

### Step 8: Re-review (if requested)

If the dev makes fixes and asks for a re-review:

1. Run `/security-review` again on the same PR.
2. Verify the `ai-team-oversight` checklist again.
3. **Replace** the entire PR description with the updated summary and review output — do not stack multiple review sections.

## Cleanup

After the PR is merged or closed:
```bash
rm -rf /tmp/repo-sync-<repo-name>
```

## Merging

**Always use the `gh` CLI to merge PRs** — the GitHub MCP tool (`merge_pull_request`) returns 404 on these repos and does not work.

```bash
gh pr merge <PR-NUMBER> --repo <main-org>/<repo-name> --squash
```

If the user asks to bypass branch protection rules, add the `--admin` flag:

```bash
gh pr merge <PR-NUMBER> --repo <main-org>/<repo-name> --squash --admin
```

Only use `--admin` when the user explicitly requests it.

## Notes

- If `repo-sync-<today's date>` branch already exists, append a counter: `repo-sync-2026-04-02-2`.
- If no matching repos are found between the orgs, report that to the user and stop.
- The user (lead dev) must have push access to the main org repos for this to work.
- **Do not use the GitHub MCP tool for merging** — it does not have the necessary permissions for these repos. Always use `gh` CLI instead.
