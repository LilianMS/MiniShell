#include "../includes/minishell.h"

/* 	testes */

void	type_tokens(int type)
{
	if (type == CMD)
		printf("Type: COMMAND");
	else if (type == ARG)
		printf("Type: ARGUMENT");
	else if (type == PIPE)
		printf("Type: PIPE");
	else if (type == REDIR_IN)
		printf("Type: REDIRECTION_IN");
	else if (type == REDIR_OUT)
		printf("Type: REDIRECTION_OUT");
	else if (type == REDIR_APPEND)
		printf("Type: REDIRECTION_APPEND");
	else if (type == VARIABLE)
		printf("Type: VARIABLE");
	else if (type == STRING)
		printf("Type: STRING");
	else
		printf("Type: UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	printf("Tokens:\n");
	while (current)
    {
		type_tokens(current->type);
		printf(", Value: %s\n", current->value);
		current = current->next;
	}
}
/* ---- */