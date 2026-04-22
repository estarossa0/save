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
2. **Otherwise:** call `ExitWorktree({ action: "keep" })`.
