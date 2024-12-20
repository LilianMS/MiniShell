#include "../includes/tokenizer.h"

int	m_validate_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current != NULL)
	{
		if ((m_is_redir(current->type) \
			&& (current->next == NULL || current->next->type != WORD)) \
			|| (current->type == PIPE && (current->next == NULL \
			|| (current->next->type != WORD && !m_is_redir(current->next->type)))))
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
	m_add_post_redir_type(tokens);
	return (1);
}

