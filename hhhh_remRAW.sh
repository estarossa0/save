#!/bin/bash

shell_f=$(echo -n "$SHELL" | awk -F / '{print $3}')
shell_f="${HOME}/.${shell_f}rc"

hidutil property --set '{"UserKeyMapping":[]}' > /dev/null
sed -i -e '/#HHH/,$d' $shell_f