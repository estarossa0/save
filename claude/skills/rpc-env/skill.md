---
name: rpc-env
description: Use when making any on-chain RPC call (cast, forge script, etc.) — provides the correct environment variable names for each network so you never hardcode RPC URLs
---

# RPC Environment Variables

When making any on-chain call (`cast`, `forge script`, `forge verify`, etc.), use these shell environment variables instead of hardcoding URLs.

## Available Variables

| Variable | Network |
|---|---|
| `$ETH_RPC` | Ethereum Mainnet |
| `$ETH_SEP_RPC` | Ethereum Sepolia |
| `$ARB_RPC` | Arbitrum Mainnet |
| `$ARB_SEP_RPC` | Arbitrum Sepolia |
| `$SOLANA_MAINNET_RPC` | Solana Mainnet-Beta |
| `$SOLANA_DEVNET_RPC` | Solana Devnet |

## Forge-style aliases (used by deployment-manager.sh)

| Variable | Points to |
|---|---|
| `$MAINNET_RPC_URL` | `$ETH_RPC` |
| `$SEPOLIA_RPC_URL` | `$ETH_SEP_RPC` |
| `$ARBITRUM_RPC_URL` | `$ARB_RPC` |

## Usage

```bash
# cast calls
cast call <address> "fn()" --rpc-url $ETH_SEP_RPC

# forge scripts (deployment-manager.sh uses NETWORK env to pick *_RPC_URL)
NETWORK=sepolia ./deployment-manager.sh <command>
```

Never hardcode RPC URLs. Always use the variable.
