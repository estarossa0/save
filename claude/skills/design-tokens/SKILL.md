---
name: design-tokens
description: Use when implementing UI from Figma, pulling frames via get_design_context, auditing colors via use_figma, or any task involving color tokens. Triggers on Figma URLs, get_design_context calls, color/token references, or UI implementation tasks.
---

# Design Tokens Usage

## Overview

Colors in this codebase come from Figma variables exported as CSS custom properties and Tailwind theme classes. The source of truth is the Figma variable **name**, never the hex value. When implementing UI from Figma, always use the token name — never hardcode hex values.

## Token Tiers

| Prefix | Purpose | Example (Figma) | Example (Tailwind) |
|--------|---------|-----------------|-------------------|
| `ref/` | Raw color primitives | `ref/earth/600` | `bg-ref-earth-600` |
| `sys/` | Semantic system tokens (alias ref) | `sys/primary/primary` | `bg-sys-primary-primary` |
| `surface/` | Surface/background tokens (alias ref) | `surface/on-surface` | `text-surface-on-surface` |
| `comp/` | Component-specific tokens (alias ref) | `comp/button/destructive/bg` | `bg-comp-button-destructive-bg` |
| `state-layers/` | Interaction/opacity states | `state-layers/primary-opacity-8` | `bg-state-layers-primary-opacity-8` |

**Always use the most specific token Figma provides.** If Figma says `comp/button/destructive/bg`, use that — don't resolve it to `ref/terracotta/500`. The designer chose that token so they can globally change it later without touching code.

Only use `ref/` tokens when Figma itself uses a `ref/` token or a raw hex.

## Figma to Tailwind Mapping

Figma variable names map to Tailwind classes by replacing `/` with `-` and adding a utility prefix. For example, `sys/outline/outline` might become `border-sys-outline-outline`.

However, **do not blindly assume this conversion is correct.** Before using any token class, verify it exists in `packages/ui/base/tailwind-theme.css` (look for `--color-<name>`). If the variable doesn't exist in the theme, flag it — it may need to be added to the token pipeline.

General mapping of utility prefixes:
- Fill → `bg-`
- Text fill → `text-`
- Stroke → `border-`

## Using `get_design_context`

`get_design_context` returns Tailwind code with variables in this format:

```
bg-[var(--surface\/surface,#fcfbf9)]
text-[color:var(--comp\/button\/destructive\/label,#fbf0ee)]
```

**Do NOT use this output as-is.** Extract the variable name (before the comma), convert to a Tailwind class, and verify:

| `get_design_context` output | Extract | Tailwind class |
|---|---|---|
| `var(--surface\/surface,#fcfbf9)` | `surface/surface` | `bg-surface-surface` |
| `var(--sys\/negative\/negative,#b05650)` | `sys/negative/negative` | `border-sys-negative-negative` |
| `var(--comp\/button\/destructive\/bg,#b05650)` | `comp/button/destructive/bg` | `bg-comp-button-destructive-bg` |

**Never use the hex fallback value.** It exists only as a Figma export artifact.

## Auditing Colors with `use_figma`

When inspecting colors in bulk via `use_figma`, always read variable bindings — never extract raw RGB hex values.

**Correct — read variable bindings:**
```js
const boundVars = node.boundVariables;
if (boundVars?.fills?.[i]) {
  const variable = await figma.variables.getVariableByIdAsync(boundVars.fills[i].id);
  const tokenName = variable.name; // e.g. "ref/teal/400"
  const twClass = tokenName.toLowerCase().replace(/\//g, "-"); // "ref-teal-400"
  // Verify twClass exists in tailwind-theme.css before using
}
```

**Wrong — extracting hex values:**
```js
// DO NOT do this — hex values drift due to rounding, aliasing, and mode resolution
const hex = rgbToHex(fill.color.r, fill.color.g, fill.color.b);
```

Hex values from Figma will often differ slightly from the hex in `variables.css` (e.g., Figma renders `ref/teal/400` as `#5F9696` but the token defines `#5F9496`). Comparing by hex leads to false mismatches. **Always compare by variable name.**

## Unbound Hex Values

If a Figma node uses a raw hex color (no variable binding):

1. **Use it as an arbitrary Tailwind value:** `bg-[#hex]`, `text-[#hex]`, `border-[#hex]`
2. **Flag it to the dev** — the dev needs to report it to the designer so the color gets bound to a token

Do not block the task over an unbound hex. Implement it and flag it.

## Common Mistakes

| Mistake | Why it's wrong | What to do instead |
|---------|---------------|-------------------|
| Hardcoding hex values from Figma | Hex values bypass the token system and can't be globally updated | Use the variable name as a Tailwind class |
| Comparing colors by hex | Resolved hex values drift between Figma and CSS due to rounding | Compare by variable name |
| Resolving `comp/` or `sys/` tokens to their `ref/` value | Loses semantic meaning, breaks future global changes | Use the token Figma specifies |
| Using `get_design_context` output as-is | Contains `var()` wrappers and hex fallbacks not valid as TW classes | Extract variable name, verify in theme, use as TW class |
| Converting `/` to `-` without checking the theme | The class may not exist | Always verify in `packages/ui/base/tailwind-theme.css` |
