---
name: delegate-browser-tasks
description: Use when running as Fable and the user asks for multi-step browser work through Playwright — logging into a dashboard (Privy, Vercel, Supabase, Stripe, etc.) and then clicking through it to create/configure something (webhooks, API keys, settings). Delegate the clicking to a Sonnet subagent instead of driving Playwright directly.
---

# Delegate Browser Tasks (Fable → Sonnet)

## Why

Playwright responses are large (accessibility snapshots, tab lists, console logs) and dashboard work takes many round-trips. Running that loop on Fable burns expensive tokens on mechanical clicking. A Sonnet subagent does it just as well for a fraction of the cost; Fable only writes the brief and reads the summary.

## When this applies

- The current model is **Fable** (check the model ID in the system prompt), AND
- The task means driving a web UI via Playwright beyond a single page load — e.g. "I logged into Privy, use Playwright to create a webhook from the dashboard".

If the current model is not Fable, ignore this skill and do the work directly.

## Rules

- **Never** click through the dashboard yourself on Fable. No `browser_snapshot`, `browser_click`, `browser_fill_form` loops in the main thread.
- One allowed exception: a single `browser_navigate` to the login page so the user can sign in. Then stop and wait for the user to confirm they're logged in.
- After login, spawn **one** subagent with `model: "sonnet"` (`subagent_type: "general-purpose"`). It uses the same Playwright MCP, so it sees the same browser and logged-in session.

## Flow

1. If the user isn't logged in yet: navigate to the dashboard login URL, ask them to log in, wait.
2. Gather the requirements before delegating. Ask the user for anything missing (e.g. webhook URL, which events, environment/app). Don't let the subagent guess.
3. Spawn the Sonnet subagent with a self-contained brief (template below).
4. Relay the subagent's result to the user: what was created, the values they need (IDs, secrets), and anything that failed.

## Brief template

```
Use the Playwright MCP tools to do this in the already-open, already-logged-in browser.

Goal: <one sentence, e.g. "Create a webhook in the Privy dashboard for app X">
Dashboard: <URL or starting page>
Requirements:
- <field>: <exact value>
- <field>: <exact value>
Constraints:
- Don't change or delete anything not listed above.
- If you hit a login page, a 2FA prompt, a payment step, or anything ambiguous, stop and report back. Don't guess.
- Don't log out or close the tab.
Report back (short):
- What you created/changed, with final values (IDs, URLs, signing secrets, anything the user must copy).
- Anything that didn't match the requirements, or errors.
```

## Red flags (you're about to violate this)

- "It's just a couple of clicks, I'll do it myself" — snapshots are still large; delegate.
- Reading a `browser_snapshot` result in the Fable thread after login.
- Spawning the subagent without concrete values, so it has to come back and ask.
