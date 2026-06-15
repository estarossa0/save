---
name: worktree-exit
description: Use when the user wants to leave the current git worktree session and return to the original directory
---

# Exit Worktree

## Usage

- `/worktree-exit` — exit and keep the worktree on disk
- `/worktree-exit remove` — exit and delete the worktree and its branch

## Steps

1. **If argument is "remove":** call `ExitWorktree({ action: "remove" })`.
   - If it fails due to uncommitted changes, show the changes and ask the user to confirm before calling with `discard_changes: true`.
   - If it fails because the worktree was NOT created by `EnterWorktree` in this session:
     1. Note the worktree path and branch name.
     2. Call `ExitWorktree({ action: "keep" })` to return to the original directory.
     3. Check for uncommitted changes in the worktree path with `git -C <path> status --porcelain`. If dirty, show changes and ask the user to confirm.
     4. Run `git worktree remove <path>` (or `git worktree remove --force <path>` if user confirmed dirty removal).
     5. Delete the branch: `git branch -D <branch>`.
     6. Remove the leftover empty directory: `rmf <path>` (git does not clean this up).
2. **Otherwise:** call `ExitWorktree({ action: "keep" })`.
