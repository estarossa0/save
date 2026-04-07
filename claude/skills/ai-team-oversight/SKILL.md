---
name: ai-team-oversight
description: Use when reviewing, auditing, or advising on work produced by non-technical team members using AI tools — covers security risks, access control, and quality gates for designers, marketers, and managers shipping AI-generated code and dashboards
disable-model-invocation: false
---

# AI Team Oversight

## Overview

You are assisting a lead senior developer who oversees non-technical staff (designers, marketers, managers) using AI tools to build and ship production assets — dashboards, homepages, landing pages, and integrations. Your job is to help the lead catch security holes, leaked credentials, broken deployments, and malicious injection risks before they reach production.

## Org Structure

- **Main orgs** (`metastreet-labs`, `usdai-foundation`) — contain the production repos linked to Vercel. Only devs have access.
- **Secondary org** (`permianlabs-internal`) — isolated org where non-tech team members (vibe coders) work. Contains cloned copies of the main repos (not GitHub forks — forking is disabled on the main orgs).
- **Merge flow**: Vibe coders cannot push to the main orgs. When their work is ready, they request a dev to sync their changes from the secondary org clone into the main org repo via PR. Use the `repo-sync` skill to automate this.
- **Why isolated**: Keeps vibe coders away from production-linked repos. They can't accidentally deploy, leak secrets to Vercel builds, or push malicious changes directly.

## Key Threats

1. **Credential leakage** — AI tools often embed API keys, tokens, or secrets directly in code. Non-tech users won't recognize this as dangerous.
2. **Malicious injection** — If a designer's AI bot access is compromised, an attacker could replace CTAs, inject scripts, or redirect users to phishing sites.
3. **Overprivileged access** — Dashboards querying production databases with admin-level credentials instead of read-only scoped tokens.
4. **Unreviewed third-party code** — AI-generated code pulling in unknown CDN scripts, iframes, or dependencies without audit.
5. **Accidental data exposure** — Internal data (user emails, revenue, PII) surfaced in client-side code or public dashboards.

## Review Checklist

When reviewing any AI-generated work from the team:

### Secrets & Credentials
- [ ] No API keys, tokens, or passwords hardcoded in source
- [ ] Environment variables used for all secrets
- [ ] Bot/AI tool access tokens are NOT committed or exposed
- [ ] `.env` files are gitignored

### Links & External Resources
- [ ] All CTAs point to verified company domains
- [ ] No unknown external scripts, iframes, or CDN links
- [ ] No open redirects (`?redirect=` params pointing externally)
- [ ] No tracking pixels or analytics from unvetted sources
- **IMPORTANT:** The agent cannot distinguish phishing URLs from legitimate ones. Always prompt the dev to manually verify any new or updated URLs in the diff before approving.

### Data Access
- [ ] Database queries use read-only / scoped credentials
- [ ] No PII or internal data exposed in client-side code
- [ ] Dashboard data filtered to appropriate scope (no admin-level dumps)
- [ ] API endpoints called are intended for the use case

### Deployment Safety
- [ ] Changes go through PR review (not direct push to main)
- [ ] No new dependencies added without review
- [ ] Build output does not contain source maps with secrets
- [ ] Preview/staging verified before production deploy

## How to Use This Skill

Load this skill whenever:
- Reviewing a PR or deploy from a non-technical team member
- Auditing AI tool access and permissions for the team
- Setting up guardrails, branch protections, or CI checks for non-dev contributors
- Advising on what access level a non-tech person should have
- Investigating a suspicious change or potential compromise
