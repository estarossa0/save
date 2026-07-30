---
name: fixing-pr-comments
description: Use when the user asks to fix, address, or pull review comments from a GitHub PR. Triggers on "fix PR comments", "pull PR comments", "address review feedback", or referencing a PR number with comments to fix.
---

# Fixing PR Review Comments

Fetch inline review comments from a GitHub PR, categorize them, create a structured fix plan, and execute fixes one by one.

## Process

### 1. Fetch Comments

```bash
gh api repos/{owner}/{repo}/pulls/{N}/comments \
  --jq '.[] | {user: .user.login, body: .body, path: .path, line: .line}'
```

Filter out bot users. Only process human reviewer comments.

### 2. Categorize

- **Actionable**: Comments requesting immediate changes — fix now
- **Post-review cleanup**: Comments containing "Post-review cleanup" — deferred, saved for later

### 3. Create Working Files

Three files in a `.review/` folder at the project root:

| File | Purpose |
|------|---------|
| `pr-{N}-fixes.md` | Full inventory of all comments with checkbox status tracking |
| `pr-{N}-fix-plan.md` | Detailed fix plan for each actionable item (file, line, what to change, why) |
| `pr-{N}-post-review.md` | Deferred post-review cleanup items (only created if any exist) |

**Fixes list format:**
```markdown
# PR #{N} Review Comments

## Actionable
- [ ] `path/to/file.ts:28` — "comment body" (@reviewer)

## Post-Review Cleanup
- [ ] `path/to/file.ts:50` — "Post-review cleanup: description" (@reviewer)
```

**Fix plan format:**
```markdown
# PR #{N} Fix Plan

## Fix 1: `path/to/file.ts:28`
**Comment:** "the reviewer comment"
**Change:** What to change and why
```

### 4. Present & Execute

- Show the full fix list to the user before starting
- Fix items one at a time
- After each fix, mark complete (`[x]`) in the fixes list
- Commit after each fix unless user says otherwise
- When all actionable fixes are done, ask the user if they want to delete `pr-{N}-fixes.md` and `pr-{N}-fix-plan.md` from `.review/`

### 5. Post-Review Cleanup

When user later asks to address post-review items, read `pr-{N}-post-review.md` and work through them. When all cleanup items are done, ask the user if they want to delete `pr-{N}-post-review.md`.

## Repo Detection

`gh` CLI auto-detects from git remote. For explicit control:
```bash
gh api repos/$(gh repo view --json nameWithOwner -q .nameWithOwner)/pulls/{N}/comments
```
