
export ZSH="$HOME/.oh-my-zsh"

ZSH_THEME="robbyrussell"

export EDITOR="cursor"

plugins=(git
        zsh-autosuggestions
        zsh-syntax-highlighting
        docker
        minikube
        kubectl
        copyfile
        docker-compose
        vscode)

source $ZSH/oh-my-zsh.sh

export EZA_CONFIG_DIR="$HOME/.eza"
alias ls="eza --icons=always"
alias c='clear'
alias ll='ls -l'
alias per='chmod a+x'
alias l.='ls -d .*'
alias ll='ls -l'
alias zlss='zless'
alias lss='less'
alias l.='ls -d .*'
alias ll='ls -l'
alias la='ls -A'
alias rm='rm -riv'
alias rmf='rm -f'
alias cp='cp -riv'
alias mv='mv -iv'
alias die='wmctrl -c chrom ;sleep 1 ; shutdown now'
alias prog="$EDITOR -r ~/.zshrc"
alias xx='source ~/.zshrc'
alias dk=docker


alias cur='cursor'
alias hh='pnpm hardhat'

alias cc='EDITOR="cursor --wait" ENABLE_CLAUDEAI_MCP_SERVERS="false" CLAUDE_CODE_NO_FLICKER="1" claude --enable-auto-mode'

# Claude commit with optional message
ccc() {
  claude -p  "/commit-commands:commit $*"
}

#nvm
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion

# pnpm
export PNPM_HOME="/Users/estarossa/.local/share/pnpm"
case ":$PATH:" in
  *":$PNPM_HOME:"*) ;;
  *) export PATH="$PNPM_HOME:$PATH" ;;
esac
# pnpm end
alias p=pnpm
alias pg_start="launchctl load ~/Library/LaunchAgents"
alias pg_stop="launchctl unload ~/Library/LaunchAgents"


eval "$(/opt/homebrew/bin/brew shellenv)"
export PATH="/opt/homebrew/opt/postgresql@17/bin:/opt/homebrew/bin:$PATH"
export PATH="/opt/homebrew/opt/libpq/bin:$PATH"
export LDFLAGS="-L/opt/homebrew/opt/postgresql@17/lib"
export CPPFLAGS="-I/opt/homebrew/opt/postgresql@17/include"

export PATH="$PATH:/Users/estarossa/.foundry/bin"

# Added by Windsurf
export PATH="/Users/estarossa/.codeium/windsurf/bin:$PATH"

export REACT_EDITOR=$EDITOR
TIMING="10"
export PATH="/Users/estarossa/.local/share/pinata:$PATH"

autoload -U compinit
compinit -i

bindkey '^[[1;3D' backward-word
bindkey '^[[1;3C' forward-word

alias senv='source .env'

export LOCALNET_URL="http://127.0.0.1:8545"

export PATH="$HOME/.local/bin:$PATH"

# Secrets — set these in a separate .env or .zshrc.local that is NOT committed
# export GITHUB_PERSONAL_ACCESS_TOKEN="..."
# export ARB_RPC="..."
# export ARB_SEP_RPC="..."
# export ETH_RPC="..."
# export ETH_SEP_RPC="..."
# export ETHERSCAN_API_KEY="..."

export ARBITRUM_RPC_URL=$ARB_RPC
export MAINNET_RPC_URL=$ETH_RPC
export SEPOLIA_RPC_URL=$ETH_SEP_RPC

_fork() {
  _describe 'chain' '(arb arb_sep eth eth_sep)'
}
compdef _fork fork

fork() {
  local chain="${1:u}_RPC"
  local rpc="${(P)chain}"
  if [[ -z "$rpc" ]]; then
    echo "Unknown chain: $1 (no env var $chain)" >&2
    return 1
  fi
  local cmd=(anvil --fork-url "$rpc" --auto-impersonate --no-cors --print-traces)
  [[ -n "$2" ]] && cmd+=(--port="$2")
  "${cmd[@]}"
}

pk() {
    export PRIVATE_KEY=$(cast wallet dk "$1" | awk '{print $NF}')
}

# bun completions
[ -s "/Users/estarossa/.bun/_bun" ] && source "/Users/estarossa/.bun/_bun"

alias b='bun'

## Directories
alias borrow="cd ~/work/metastreet/main/usdai-borrow"
alias usdai="cd ~/work/metastreet/main/usdai-frontend/"
alias data="cd ~/work/metastreet/main/metastreet-data/"
alias crucible="cd ~/work/personal/crucible/"
alias work="cd ~/work/"
alias main="cd ~/work/metastreet/main/"

## Shortcuts
alias dev="p dev"
alias build="p build"



test -e "${HOME}/.iterm2_shell_integration.zsh" && source "${HOME}/.iterm2_shell_integration.zsh"



# bun
export BUN_INSTALL="$HOME/.bun"
export PATH="$BUN_INSTALL/bin:$PATH"
