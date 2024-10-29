#include "../includes/tokenizer.h"

#include <stdio.h> // -- debug

int	m_validate_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == PIPE || current->type == REDIR_IN \
			|| current->type == REDIR_OUT || current->type == REDIR_HEREDOC \
			|| current->type == REDIR_APPEND)
		{
			if (current->prev == NULL || current->prev->type != WORD) {
				printf("Error: Expected a word before the operator.\n"); // -- debug
				return (0);
			}
			if (current->next == NULL || current->next->type != WORD) {
				printf("Error: Expected a word after the operator.\n"); // -- debug
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

