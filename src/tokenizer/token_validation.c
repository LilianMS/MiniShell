#include "../includes/tokenizer.h"

/*
int	m_validate_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if ((m_is_redir(current->type) \
			&& (current->next == NULL || current->next->type != WORD)) \
			|| (current->type == PIPE \
			&& (current->next == NULL \
			|| (current->next->type != WORD && current->next->type != REDIR_IN))))
		{
				ft_putendl_fd("Error: Expected a word or input redirection after the pipe.", 2);
				return (0);
		}
		if (current->type == PIPE && (current->prev == NULL || current->prev->type != WORD))
		{
			ft_putendl_fd("Error: Expected a word before the operator.", 2);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
*/

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
			if (current->next == NULL || current->next->type != WORD)
			{
				ft_putendl_fd("Error: Expected a word after the operator.", 2);
				return (0);
			}
			if (current->type == PIPE
				&& (current->prev == NULL || current->prev->type != WORD))
			{
				ft_putendl_fd("Error: Expected a word before the operator.", 2);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}
