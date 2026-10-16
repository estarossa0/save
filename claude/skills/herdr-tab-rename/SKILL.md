---
name: herdr-tab-rename
description: Use when the user wants to rename the current Herdr tab (e.g. "rename this tab", "name the tab X", "/herdr-tab-rename X")
---

# Rename Current Herdr Tab

## Usage

- `/herdr-tab-rename <label>` — rename the current tab to `<label>`
- `/herdr-tab-rename` — use the session name; only if the session has no name, pick a short label (1–3 words) from the current task/conversation

## Steps

1. Verify running inside Herdr: `test "${HERDR_ENV:-}" = 1 && test -n "${HERDR_TAB_ID:-}"`. If not, tell the user this session isn't in a Herdr pane and stop.
2. Determine the label, in this order:
   1. The argument, if given.
   2. The session name, if the session has one — e.g. the most recent `Session renamed to: <name>` output from `/rename` in the conversation. Use it verbatim.
   3. Only if the session has no name: derive a short label (1–3 words) from the current work.
3. Rename the tab hosting this session (not the UI-focused one) and read back the new label:
   ```bash
   herdr tab rename "$HERDR_TAB_ID" "<label>" | jq -r .result.tab.label
   ```
4. Report the printed label. On failure the command exits 1 and prints `{"error":{"code":...,"message":...}}` — report that message.

## Notes

- `HERDR_TAB_ID` (e.g. `w2:t4`) is injected into every Herdr-managed pane — always use it rather than guessing from `herdr tab list`.
- The rename response already contains the updated tab, so no separate `herdr tab get` is needed.
