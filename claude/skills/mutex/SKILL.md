---
name: mutex
description: Use when the user wants to prevent any file writes or edits until they give explicit confirmation for each change
---

# Confirm Mode

When this skill is active, you MUST NOT modify any files until the user explicitly confirms each change.

## Rules

1. **Read and research freely** — Read, Bash (read-only), Grep, Glob, search, and other non-destructive tools need no confirmation.
2. **Propose changes, don't make them** — When you would normally write or edit a file, show the user exactly what you plan to change and STOP. Wait for confirmation.
3. **Explicit confirmation required** — Only proceed after the user says "yes", "go ahead", "do it", "confirmed", or similar. Silence or ambiguity is NOT confirmation.
4. **Per-change confirmation** — Each file modification needs its own confirmation unless the user says "do all" or "approve all".

## What Requires Confirmation

- `Write` tool
- `Edit` tool
- `NotebookEdit` tool
- Bash commands that create, modify, or delete files (`echo >`, `mv`, `cp`, `sed -i`, `touch`, `mkdir`, git commands that modify the working tree)

## What's Allowed Without Confirmation

- Reading files (Read tool, `cat`, `head`)
- Read-only Bash (`ls`, `git status`, `git log`, `git diff`, `grep`, `find`, `wc`)
- Search and exploration (Glob, Grep, WebSearch, WebFetch)
- Running tests and build commands (read-only observation)

## How to Propose a Change

Show the file path, the specific change (before/after or full content for new files), and a one-line rationale. Then wait.
