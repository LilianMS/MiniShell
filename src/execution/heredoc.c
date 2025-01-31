#include "../../includes/minishell.h"

char	*m_heredoc_get_delimiter(t_token *node, t_hdoc *hdoc)
{
	if (node == NULL || node->next == NULL)
		return (NULL);
	if (node->next->type == DELIMITER)
	{
		hdoc->nb_line_del = m_update_nb_lines(-1);
		return (node->next->lexeme);
	}
	return (NULL);
}

int	m_init_heredoc(t_hdoc *hdoc, t_token *node)
{
	if (!hdoc)
	{
		perror("Error: hdoc is not initialized");
		return (1);
	}
	hdoc->exit_flag = 0;
	hdoc->history_block = NULL;
	hdoc->delimiter = m_heredoc_get_delimiter(node, hdoc);
	if (!hdoc->delimiter)
	{
		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
		return (1);
	}
	hdoc->temp_fd = heredoc_create_file(&hdoc);
	if (hdoc->temp_fd == -1)
		return (1);
	heredoc_signals();
	return (0);
}

void	m_heredoc_update_node(t_token **node, t_hdoc *hdoc)
{
	if ((*node)->next->type == DELIMITER \
		&& ft_strcmp((*node)->next->lexeme, hdoc->delimiter) == 0)
	{
		free((*node)->next->lexeme);
		(*node)->next->lexeme = ft_strdup(hdoc->filename);
		g_signal_status = 256;
	}
}

int	m_heredoc( t_token **parsed_list, t_mini *mini)
{
	t_token	*current;
	t_hdoc	*hdoc;

	current = *parsed_list;
	while (current)
	{
		if (current->type == REDIR_HEREDOC)
		{
			hdoc = mini->hdoc;
			if (m_init_heredoc(hdoc, current))
				return (-1);
			m_aux_heredoc(hdoc, current, mini);
			if (mini->hdoc->exit_flag == 1)
				print_heredoc_message(hdoc);
			if (g_signal_status != 130)
				m_heredoc_update_node(&current, hdoc);
			close(hdoc->temp_fd);
			m_exec_signals(1);
			if (g_signal_status == 130)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
