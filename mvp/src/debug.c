#include "../includes/minishell.h"

/* 	testes */



void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	printf("Tokens:\n");
	while (current)
    {
		printf("Type: %d, Value: %s\n", current->type, current->value);
		current = current->next;
	}
}
/* ---- */