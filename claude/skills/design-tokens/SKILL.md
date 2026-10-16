---
name: design-tokens
description: Use when implementing UI from Figma, pulling frames via get_design_context, auditing colors via use_figma, or any task involving color tokens, spacing, or radius. Triggers on Figma URLs, get_design_context calls, color/token/spacing/radius references, or UI implementation tasks.
---

# Design Tokens Usage

## Overview

Design tokens in this codebase (colors, spacing, radius) come from Figma variables exported via Tokens Studio as a multi-file folder, then processed by Style Dictionary into CSS custom properties and Tailwind theme classes. The source of truth is the Figma variable **name**, never the raw value. When implementing UI from Figma, always use the token name — never hardcode hex values or pixel numbers.

## Token Pipeline

Source files live in `packages/ui/base/tokens/` (Tokens Studio multi-file export):

```
tokens/
  Themes/Light.json    → color tokens (ref, sys, surface, comp, state-layers)
  Spacing/Default.json → spacing, padding, container tokens
  Radius/Default.json  → radius tokens + semantic aliases (button, round, etc.)
  Opacity/Mode 1.json  → opacity, typography, shadows (not yet wired)
  $themes.json         → theme config (empty — no dark mode yet)
  $metadata.json       → set ordering
```

Run `tsx --tsconfig tsconfig.json base/convertTokensToCss.ts` from `packages/ui/` to regenerate:
- `base/variables.css` — `:root` CSS custom properties (colors, spacing, radius)
- `base/tailwind-theme.css` — `@theme` block mapping tokens to Tailwind namespaces
- `base/typography.css` — `:root` CSS custom properties for text styles (font shorthand)
- `base/typography-utilities.css` — `@utility` rules for text style classes (`text-label-xl-500`, etc.)

## Token Tiers

### Color Tokens

| Prefix | Purpose | Example (Figma) | Example (Tailwind) |
|--------|---------|-----------------|-------------------|
| `ref/` | Raw color primitives | `ref/earth/600` | `bg-ref-earth-600` |
| `sys/` | Semantic system tokens (alias ref) | `sys/primary/primary` | `bg-sys-primary-primary` |
| `surface/` | Surface/background tokens (alias ref) | `surface/on-surface` | `text-surface-on-surface` |
| `comp/` | Component-specific tokens (alias ref) | `comp/button/destructive/bg` | `bg-comp-button-destructive-bg` |
| `state-layers/` | Interaction/opacity states | `state-layers/primary-opacity-8` | `bg-state-layers-primary-opacity-8` |

**Always use the most specific token Figma provides.** If Figma says `comp/button/destructive/bg`, use that — don't resolve it to `ref/terracotta/500`. The designer chose that token so they can globally change it later without touching code.

Only use `ref/` tokens when Figma itself uses a `ref/` token or a raw hex.

### Spacing Tokens

Spacing tokens use a `Xpx` suffix in Tailwind (e.g. `--spacing-8px`) to avoid colliding with Tailwind's built-in rem-based scale (where `p-4` = `1rem` = `16px`). The `px` suffix makes the unit explicit and prevents accidental misuse.

| Group | CSS var | Tailwind class | Value |
|-------|---------|---------------|-------|
| `spacing/` | `--spacing-8` | `p-8px`, `gap-8px`, `m-8px` | `8px` |
| `padding/` | `--padding-8` | `p-padding-8px` | `8px` |
| `container/` | `--container-lg` | `h-container-lg` | `40px` |

**`p-8` vs `p-8px`**: `p-8` is Tailwind's built-in `2rem` (32px). `p-8px` is the Figma design token `8px`. Always use the `px` suffix when referencing design tokens.

Available spacing values: `0, 1, 2, 4, 6, 8, 10, 12, 16, 20, 24, 28, 32, 36, 40, 48, 56, 64, 72, 80, 88, 96, 112, 120, 128, ...`

Container sizes: `xxxxs (16px)`, `xxxs (20px)`, `xxs (24px)`, `xs (28px)`, `sm (32px)`, `md (36px)`, `lg (40px)`

### Radius Tokens

Radius tokens use the same `Xpx` suffix pattern for numeric values. Semantic aliases (e.g. `button`, `round`) don't need a suffix since they don't collide with Tailwind defaults.

| Group | CSS var | Tailwind class | Value |
|-------|---------|---------------|-------|
| `radius/` | `--radius-6` | `rounded-6px` | `6px` |
| `button` | `--button` | `rounded-button` | `6px` |
| `round` | `--round` | `rounded-round` | `9999px` |
| `icon` | `--icon` | `rounded-icon` | `4px` |
| `minor` | `--minor` | `rounded-minor` | `1px` |

**Use semantic radius tokens when Figma specifies them** (e.g., `rounded-button`, `rounded-round`) instead of raw values like `rounded-6px`.

### Typography Tokens

Typography tokens are composite text styles exported from Figma. Each token encodes font-family, weight, size, line-height, and letter-spacing. They are output as `@utility` rules (not `@theme` vars) because the CSS `font` shorthand can't be applied through Tailwind's built-in namespaces.

Usage: `text-{style}-{size}-{weight}` — applies the full `font` shorthand + `letter-spacing` in one class.

| Style | Font | Sizes | Example class |
|-------|------|-------|--------------|
| `label` | SwissNow | xxl → xs (16→10px) | `text-label-xl-500` |
| `label/mono` | Azeret Mono | lg → sm (12→10px) | `text-label-mono-md-500` |
| `footnote` | SwissNow | md → xs (12→10px) | `text-footnote-md-400` |
| `title` | SwissNow | xxl → sm (28→14px) | `text-title-lg-500` |
| `body` | SwissNow | lg → sm (14→12px) | `text-body-lg-400` |
| `display` | PP Eiko | md → xs (32→18px) | `text-display-sm-500` |
| `metric` | SwissNow | lg → sm (32→18px) | `text-metric-lg-500` |

Weight suffixes: `400` = Regular, `500` = Medium.

Letter-spacing is applied automatically: `label` gets `-0.01em`, `metric` gets `-0.02em`, `label/mono-sm` gets `+0.02em`, others are `0`.

CSS vars are in `typography.css` (e.g. `--label-xl-500: 500 14px/1 SwissNow`). Use the `text-*` utility class, not the var directly — the utility also applies letter-spacing.

## Figma to Tailwind Mapping

Figma variable names map to Tailwind classes by replacing `/` with `-` and adding a utility prefix. For example, `sys/outline/outline` might become `border-sys-outline-outline`.

However, **do not blindly assume this conversion is correct.** Before using any token class, verify it exists in `packages/ui/base/tailwind-theme.css`. Color tokens use `--color-<name>`, spacing tokens use `--spacing-<N>px`, and radius tokens use `--radius-<N>px` or `--radius-<name>`. If the variable doesn't exist in the theme, flag it — it may need to be added to the token pipeline.

General mapping of utility prefixes:
- Fill → `bg-`
- Text fill → `text-`
- Stroke → `border-`
- Padding → `p-`, `px-`, `py-`, `pt-`, `pr-`, `pb-`, `pl-`
- Margin → `m-`, `mx-`, `my-`, etc.
- Gap → `gap-`, `gap-x-`, `gap-y-`
- Width/Height → `w-`, `h-`, `size-`
- Border radius → `rounded-`, `rounded-t-`, `rounded-l-`, etc.

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

## Never Guess Colors from Screenshots

**Do NOT assume a token from how a color looks in a screenshot or `get_design_context` output.** Two tokens can render to visually identical colors (e.g., `ref/teal/500` and `sys/positive/positive` both look teal). Before writing any color class, use `use_figma` to inspect the node's `boundVariables` and resolve the actual variable name. If you skip this step you will pick the wrong token.

Workflow: `get_design_context` / `get_screenshot` → identify which node carries the color → `use_figma` to read `boundVariables` → resolve variable name → convert to Tailwind class → verify in theme.

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
| Guessing a token from a screenshot's visual color | Visually similar colors map to different semantic tokens (e.g., `ref/teal/500` vs `sys/positive/positive`) | Always inspect `boundVariables` via `use_figma` before writing any color class |
| Hardcoding `px` values for spacing/radius | Bypasses the token system | Use the token class (e.g., `p-8px` not `p-[8px]`) |
| Using `p-8` for Figma spacing token `spacing/8` | `p-8` is Tailwind's built-in `2rem` (32px), not the design token `8px` | Use `p-8px` to reference the design token |
| Using raw radius values instead of semantic tokens | `rounded-6px` works but `rounded-button` is the intended token | Use the semantic name when Figma specifies `button`, `round`, `icon`, etc. |
