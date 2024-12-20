#include "../../includes/minishell.h"

int	ft_create_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		perror("Error creating temp file");
	return (fd);
}

char	*m_heredoc_get_delimiter(t_token *parsed_list)
{
	t_token	*current;

	current = parsed_list;
	while (current)
	{
		if (current->type == DELIMITER)
		{
			// ft_printf("DELIMITER: %s\n", current->lexeme); // ----- debug
			// if (current->quote == 0)
			// 	ft_printf("expandir in heredoc: %s\n", current->lexeme); // ----- debug
			// else
			// 	ft_printf("não expandir in heredoc: %s\n", current->lexeme); // ----- debug
			return (current->lexeme);
		}
		current = current->next;
	}
	return (NULL);
}

void	m_heredoc(t_token **parsed_list, t_mini mini)
{
	t_hdoc	*hdoc;

	hdoc = mini.hdoc;
	hdoc->exit_flag = 0;
	hdoc->env_list = mini.env_list;
	hdoc->parsed_list = *parsed_list;
	hdoc->delimiter = m_heredoc_get_delimiter(*parsed_list);
	if (!hdoc->delimiter)
	{
		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
		return ;
	}
	hdoc->temp_fd = ft_create_file(".heredoc_tmp");
	if (hdoc->temp_fd == -1)
		return ;
	m_aux_heredoc(hdoc);
	if (hdoc->exit_flag == 0)
		ft_printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s'\n", hdoc->delimiter);
	else
		m_heredoc_update_command_list(parsed_list, hdoc);
	close(hdoc->temp_fd);
	unlink(".heredoc_tmp");
	ft_printf("heredoc: exec?\n"); // ---debug
}
