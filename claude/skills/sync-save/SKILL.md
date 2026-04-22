---
name: sync-save
description: Use when creating or moving a personal skill to ensure it is saved in the correct location with the proper symlink setup
---

# Sync Save

Personal skills are stored in a git-tracked save directory and symlinked into `~/.claude/skills/`.

## Setup

- **Save directory:** `/Users/estarossa/work/tmp/save/claude/skills/`
- **Symlink target:** `~/.claude/skills/<skill-name>`
- **Repo:** `estarossa0/save` on GitHub (branch: `master`)

## When Creating a New Skill

1. Create the skill directory and `SKILL.md` in the save directory:
   ```
   /Users/estarossa/work/tmp/save/claude/skills/<skill-name>/SKILL.md
   ```
2. Create a symlink from `~/.claude/skills/`:
   ```bash
   ln -s /Users/estarossa/work/tmp/save/claude/skills/<skill-name> ~/.claude/skills/<skill-name>
   ```
3. Commit and push from the save repo.

## Never

- Write skills directly into `~/.claude/skills/` as plain directories — they won't be tracked or backed up.
- Break existing symlinks when modifying skills.
