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

## After creating a new worktree

Only when a new worktree was created (not when entering an existing one):

4. **Copy env files from the main checkout.** List them with:
   ```
   find . -name ".env*" -not -path "*/node_modules/*" -not -path "./.claude/worktrees/*" -not -path "*/.git/*"
   ```
   run from the main checkout root. Copy every match into the worktree at the same
   relative path (`mkdir -p` the parent first). Skip files tracked in git, such as
   `.env.example`.
5. **Rename the auto-generated branch.** `EnterWorktree` creates
   `worktree-<name>`; rename it to the `esta/<verb>-<subject>` convention:
   ```
   git branch -m esta/<verb>-<name>
   ```
   Pick the verb from the work the worktree is for (`add`, `update`, `remove`, `fix`).
6. **Install dependencies.** A fresh worktree has no `node_modules`. Determine the
   package manager from the lockfile committed in the repo (`git ls-files | grep lock`),
   not from untracked files, then run its install from the worktree root.
