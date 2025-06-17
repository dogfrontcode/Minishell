#include "../../includes/minishell.h"

static int	is_empty_line(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

void	handle_prompt(char *input)
{
	// Aqui entra o parser, mas por enquanto imprimimos algo simples
	printf("🛠️  (parser e exec virão aqui)\n");

	// Exemplo: Se quiser testar parseamento básico depois, pode imprimir tokens
	// Ex: parse_input(input); execute_commands(parsed);

	// Este é apenas um esqueleto de placeholder
      
	if (is_empty_line(input))
		return ;
	printf("🛠️  Comando recebido: %s\n", input);
}

