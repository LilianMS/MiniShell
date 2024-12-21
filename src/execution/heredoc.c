#include "../../includes/minishell.h"

int	ft_create_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		perror("Error creating temp file");
	return (fd);
}

int	heredoc_create_file(t_hdoc **hdoc)
{
	char	filename[256];
	char	*suffix;
	int		fd;

	if ((*hdoc)->suffix_doc == -1)
		(*hdoc)->suffix_doc = 0;
	suffix = ft_itoa((*hdoc)->suffix_doc);
	strcpy(filename, ".heredoc");
	strcat(filename, suffix);
	free(suffix);
	fd = ft_create_file(filename);
	if (fd != -1)
		((*hdoc)->suffix_doc)++;
	(*hdoc)->filename = filename;
	return (fd);
}

char	*m_heredoc_get_delimiter(t_token *parsed_list)
{
	t_token	*current;

	current = parsed_list;
	while (current)
	{
		if (current->type == DELIMITER)
			return (current->lexeme);
		current = current->next;
	}
	return (NULL);
}

void	m_heredoc_update_token_list(t_token **token_list, t_hdoc *hdoc)
{
	t_token *current;

	current = *token_list;
	while (current)
	{
		if (current->type == DELIMITER && ft_strcmp(current->lexeme, hdoc->delimiter) == 0)
		{
			free(current->filename);
			current->filename = hdoc->filename;
			current->type = FILENAME;
		}
		current = current->next;
	}
}

void	m_heredoc(t_token **token_list, t_mini mini)
{
	t_hdoc	*hdoc;

	hdoc = mini.hdoc;
	hdoc->exit_flag = 0;
	hdoc->env_list = mini.env_list;
	hdoc->token_list = *token_list;
	hdoc->delimiter = m_heredoc_get_delimiter(*token_list);
	if (!hdoc->delimiter)
	{
		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
		return ;
	}
	hdoc->temp_fd = heredoc_create_file(&hdoc);
	if (hdoc->temp_fd == -1)
		return ;
	m_aux_heredoc(hdoc);
	if (hdoc->exit_flag == 0)
		ft_printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s'\n", hdoc->delimiter);
	else if (g_signal_status != 130)
		m_heredoc_update_token_list(token_list, hdoc);
	close(hdoc->temp_fd);
	ft_printf("heredoc: exec?\n"); // ---debug
	// signal(SIGINT, m_sig_int);
}




// void	m_heredoc(t_token **parsed_list, t_mini mini)
// {
// 	t_hdoc				*hdoc;

// 	hdoc = mini.hdoc;
// 	hdoc->exit_flag = 0;
// 	hdoc->env_list = mini.env_list;
// 	hdoc->parsed_list = *parsed_list;
// 	hdoc->delimiter = m_heredoc_get_delimiter(*parsed_list);
// 	// signal(SIGINT, heredoc_sigint);
// 	// g_signal_status = 0;
// 	if (!hdoc->delimiter)
// 	{
// 		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
// 		return ;
// 	}
// 	hdoc->temp_fd = ft_create_file(".heredoc_tmp");
// 	if (hdoc->temp_fd == -1)
// 		return ;
// 	m_aux_heredoc(hdoc);
// 	if (hdoc->exit_flag == 0)
// 		ft_printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s'\n", hdoc->delimiter);
// 	else
// 		m_heredoc_update_command_list(parsed_list, hdoc);
// 	close(hdoc->temp_fd);
// 	unlink(".heredoc_tmp");
// 	ft_printf("heredoc: exec?\n"); // ---debug
// 	// Restaura o comportamento padrão de SIGINT
// 	// signal(SIGINT, m_sig_int);
// }

// t_token	*current;
// 	t_token	*new_token;
// 	t_token	*prev;

// 	current = hdoc->token_list;
// 	prev = NULL;
// 	while (current)
// 	{
// 		if (current->type == REDIR_HEREDOC)
// 		{
// 			new_token = malloc(sizeof(t_token));
// 			ft_bzero(new_token, sizeof(t_token));
// 			new_token->lexeme = ft_strdup(hdoc->filename);
// 			new_token->type = FILENAME;
// 			new_token->quote = 0;
// 			new_token->next = current->next;
// 			new_token->prev = prev;
// 			if (prev)
// 				prev->next = new_token;
// 			else
// 				*token_list = new_token;
// 			free(current->lexeme);
// 			free(current);
// 			current = new_token;
// 		}
// 		prev = current;
// 		current = current->next;
// 	}