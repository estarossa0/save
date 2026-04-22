---
name: worktree-enter
description: Use when the user wants to enter or switch to a git worktree — lists existing worktrees to pick from, or enters the one specified as an argument
---

# Enter Worktree

## Usage

- `/worktree-enter` — list existing worktrees and ask the user to pick one, or create new
- `/worktree-enter my-feature` — enter the worktree named `my-feature` directly

## Steps

1. Run `git worktree list` to get all current worktrees.
2. **If the user provided a name as argument:**
   - Find the matching worktree from the list.
   - If found, call `EnterWorktree({ path: "<matching path>" })`.
   - If not found, offer to create it: call `EnterWorktree({ name: "<argument>" })`.
3. **If no argument provided:**
   - Display the worktree list in a readable format (name, branch, path).
   - Ask the user to pick one by name/number, or type "new" to create a fresh one.
   - Enter the chosen worktree with `EnterWorktree({ path })` or create with `EnterWorktree({ name })`.

## Notes

- Worktrees live in `.claude/worktrees/` by default.
- You cannot enter a worktree if you're already in one — exit first with `/worktree-exit`.
