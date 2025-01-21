#include "../../includes/minishell.h"

void	update_history(char *line, char **history_block)
{
	char	*new_block;

	if (*history_block)
		new_block = malloc(strlen(*history_block) + strlen(line) + 2);
	else
		new_block = malloc(strlen(line) + 2);
	if (!new_block)
	{
		perror("Error allocating memory");
		free(line);
		return ;
	}
	if (*history_block)
	{
		ft_strcpy(new_block, *history_block);
		ft_strcat(new_block, "\n");
		free(*history_block);
	}
	else
		new_block[0] = '\0';
	ft_strcat(new_block, line);
	*history_block = new_block;
}

void	init_history_block(char **history_block, char *delimiter)
{
	*history_block = malloc(strlen("<< ") + strlen(delimiter) + 2);
	if (!*history_block)
	{
		perror("Error allocating memory");
		return ;
	}
	ft_strcpy(*history_block, "<< ");
	ft_strcat(*history_block, delimiter);
	ft_strcat(*history_block, "\n");
}

char	*m_heredoc_expansion(char *lexeme, t_env *env_list)
{
	char	*dollar_position;

	dollar_position = ft_strchr(lexeme, '$');
	if (dollar_position)
	{
		if (ft_strchr(lexeme, '\'') || ft_strchr(lexeme, '\"'))
		{
			return (m_get_expand_split(lexeme, env_list));
		}
		else if (dollar_position[1] == '\0')
			return (m_clean_quotes(ft_strdup(lexeme)));
		else
			return (m_get_expand_string(ft_strdup(lexeme), env_list));
	}
	else if (ft_strchr(lexeme, '\'') || ft_strchr(lexeme, '\"'))
		return (m_set_split_quotes(lexeme));
	return (m_clean_quotes(ft_strdup(lexeme)));
}

void	heredoc_write_to_file(t_hdoc *hdoc, char *line, t_tree *node)
{
	// t_token	*current;
	char	*expanded_line;

	// current = hdoc->token_list;
	// while (current)
	// {
		if (node->type == DELIMITER \
			&& ft_strcmp(node->content, hdoc->delimiter) == 0)
		{
			if (node->quote == 0)
			{
				expanded_line = m_heredoc_expansion(line, hdoc->env_list);
				line = expanded_line;
			}
			// break ;
		}
	// 	current = current->next;
	// }
	write(hdoc->temp_fd, line, strlen(line));
	write(hdoc->temp_fd, "\n", 1);
	free(line);
}

// void	heredoc_write_to_file(t_hdoc *hdoc, char *line)
// {
// 	t_token	*current;
// 	char	*expanded_line;

// 	current = hdoc->token_list;
// 	while (current)
// 	{
// 		if (current->type == DELIMITER \
// 			&& ft_strcmp(current->lexeme, hdoc->delimiter) == 0)
// 		{
// 			if (current->quote == 0)
// 			{
// 				expanded_line = m_heredoc_expansion(line, hdoc->env_list);
// 				line = expanded_line;
// 			}
// 			break ;
// 		}
// 		current = current->next;
// 	}
// 	write(hdoc->temp_fd, line, strlen(line));
// 	write(hdoc->temp_fd, "\n", 1);
// 	free(line);
// }

void	m_aux_heredoc(t_hdoc *hdoc, t_tree *node)
{
	char	*line;
	char	*history_block;

	line = NULL;
	history_block = NULL;
	init_history_block(&history_block, hdoc->delimiter);
	while ((line = readline("> ")) != NULL)
	{
		// line = readline("> ");
		if (g_signal_status == 130)
			line = NULL;
		if (!line || ft_strcmp(line, hdoc->delimiter) == 0 \
			|| g_signal_status == 130)
		{
			if (line && g_signal_status != 130)
				hdoc->exit_flag = 1;
			break ;
		}
		update_history(line, &history_block);
		heredoc_write_to_file(hdoc, line, node);
	}
	// criar função para adicionar history
	if (hdoc->exit_flag == 1)
		update_history(hdoc->delimiter, &history_block);
	if (history_block)
	{
		add_history(history_block);
		free(history_block);
	}
}
