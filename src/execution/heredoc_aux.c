#include "../../includes/minishell.h"

void	update_history(t_hdoc *hdoc, char *line)
{
	char	*new_block;

	if (hdoc->history_block)
		new_block = malloc(ft_strlen(hdoc->history_block) + ft_strlen(line) + 2);
	else
		new_block = malloc(ft_strlen(line) + 2);
	if (!new_block)
	{
		perror("Error allocating memory");
		free(line);
		return ;
	}
	if (hdoc->history_block)
	{
		ft_strcpy(new_block, hdoc->history_block);
		ft_strcat(new_block, "\n");
		free(hdoc->history_block);
	}
	else
		new_block[0] = '\0';
	ft_strcat(new_block, line);
	hdoc->history_block = new_block;
}

void	init_history_block(t_hdoc *hdoc)
{
	hdoc->history_block = malloc(strlen("<< ") + strlen(hdoc->delimiter) + 2);
	if (!hdoc->history_block)
	{
		perror("Error allocating memory");
		return ;
	}
	ft_strcpy(hdoc->history_block, "<< ");
	ft_strcat(hdoc->history_block, hdoc->delimiter);
	ft_strcat(hdoc->history_block, "\n");
}

char	*m_heredoc_expansion(char *lexeme, t_mini *mini)
{
	char	*dollar_position;

	dollar_position = ft_strchr(lexeme, '$');
	if (dollar_position)
	{
		if (ft_strchr(lexeme, '\'') || ft_strchr(lexeme, '\"'))
		{
			return (m_get_expand_split(lexeme, mini));
		}
		else if (dollar_position[1] == '\0')
			return (m_clean_qts(ft_strdup(lexeme)));
		else
			return (m_get_expand_string(ft_strdup(lexeme), mini));
	}
	else if (ft_strchr(lexeme, '\'') || ft_strchr(lexeme, '\"'))
		return (m_set_split_quotes(lexeme));
	return (m_clean_qts(ft_strdup(lexeme)));
}

void	heredoc_write_to_file(t_hdoc *hdoc, char *line, t_token *node, t_mini *mini)
{
	char	*expanded_line;

	if (node->next->type == DELIMITER \
		&& ft_strcmp(node->next->lexeme, hdoc->delimiter) == 0)
	{
		if (node->next->quote == 0)
		{
			expanded_line = m_heredoc_expansion(line, mini);
			line = expanded_line;
		}
	}
	write( hdoc->temp_fd, line, strlen(line));
	write( hdoc->temp_fd, "\n", 1);
	free(line);
}

void	hdoc_handle_line(t_hdoc *hdoc, char *line, t_token *node, t_mini *mini)
{
	if (ft_strcmp(line, hdoc->delimiter) == 0)
		return ;
	if (!line || g_signal_status == 130)
		return ;
	update_history(hdoc, line);
	heredoc_write_to_file(hdoc, line, node, mini);
}

void	m_aux_heredoc(t_hdoc *hdoc, t_token *node, t_mini *mini)
{
	char	*line;

	init_history_block(hdoc);
	line = readline("> ");
	while (line != NULL)
	{
		hdoc_handle_line(hdoc, line, node, mini);
		if (ft_strcmp(line, hdoc->delimiter) == 0 || g_signal_status == 130)
			break ;
		line = readline("> ");
	}
	if (!line && g_signal_status != 130)
		hdoc->exit_flag = 1;
	ft_printf("flag: %d\n", hdoc->exit_flag); // ---debug
	if (hdoc->history_block)
	{
		add_history(hdoc->history_block);
		free(hdoc->history_block);
	}
}
