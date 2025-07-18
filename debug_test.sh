#!/bin/bash

MINISHELL_PATH="../minishell"
teste="echo hello world"

echo "=== DEBUG TESTE ==="
echo "Comando: $teste"

echo "=== TESTE DIRETO ==="
echo -e "$teste" | $MINISHELL_PATH

echo "=== TESTE COM FILTROS ==="
REMOVE_COLORS="sed s/\x1B\[[0-9;]\{1,\}[A-Za-z]//g"
REMOVE_EXIT="grep -v ^exit$"
PROMPT=$(echo -e "\nexit\n" | $MINISHELL_PATH | head -n 1 | $REMOVE_COLORS)

echo "Prompt detectado: '$PROMPT'"

MINI_OUTPUT=$(echo -e "$teste" | $MINISHELL_PATH 2> /dev/null | $REMOVE_COLORS | grep -vF "$PROMPT" | $REMOVE_EXIT)

echo "Output capturado: '$MINI_OUTPUT'"

BASH_OUTPUT=$(echo -e "$teste" | bash 2> /dev/null)
echo "Output bash: '$BASH_OUTPUT'"

if [[ "$MINI_OUTPUT" == "$BASH_OUTPUT" ]]; then
    echo "✅ PASSOU"
else
    echo "❌ FALHOU"
fi 