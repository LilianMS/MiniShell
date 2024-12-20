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
		return;
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

void	write_to_temp_file(t_hdoc *hdoc, char *line)
{
	t_token	*current;
	char	*expanded_line;

	current = hdoc->parsed_list;
	while (current)
	{
		if (current->type == DELIMITER && ft_strcmp(current->lexeme, hdoc->delimiter) == 0)
		{
			if (current->quote == 0)
			{
				ft_printf("expandir in heredoc: %s\n", current->lexeme); // ----- debug
				expanded_line = m_heredoc_expansion(line, hdoc->env_list);
				free(line);
				line = expanded_line;
			}
			else
				ft_printf("não expandir in heredoc: %s\n", current->lexeme); // ----- debug
			break ;
		}
		current = current->next;
	}
	write(hdoc->temp_fd, line, strlen(line));
	write(hdoc->temp_fd, "\n", 1);
	free(line);
}

// void	write_to_temp_file(int temp_fd, char *line, char *delimiter, t_token *parsed_list)
// {
// 	t_token	*current;
// 	int		expand;
// 	char	*expanded_line;

// 	expand = 0;
// 	current = parsed_list;
// 	while (current)
// 	{
// 		if (current->type == DELIMITER && ft_strcmp(current->lexeme, delimiter) == 0)
// 		{
// 			if (current->quote == 0)
// 				ft_printf("expandir in heredoc: %s\n", current->lexeme); // ----- debug
// 			else
// 				ft_printf("não expandir in heredoc: %s\n", current->lexeme); // ----- debug
// 			break ;
// 		}
// 		current = current->next;
// 	}
// 	if (expand == 1)
// 	{
// 		expanded_line = m_clean_quotes(line);
// 		free(line);
// 		line = expanded_line;
// 	}
// 	write(temp_fd, line, strlen(line));
// 	write(temp_fd, "\n", 1);
// 	free(line);
// }

// {
// 	write(temp_fd, line, strlen(line));
// 	write(temp_fd, "\n", 1);
// 	free(line);
// }

void	aux_heredoc(t_hdoc *hdoc)
{
	char	*line;
	char	*history_block;

	line = NULL;
	history_block = NULL;
	init_history_block(&history_block, hdoc->delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, hdoc->delimiter) == 0)
		{
			if (line)
				hdoc->i = 1;
			break ;
		}
		update_history(line, &history_block);
		write_to_temp_file(hdoc, line);
	}
	if (hdoc->i == 1)
		update_history(hdoc->delimiter, &history_block);
	if (history_block)
	{
		add_history(history_block);
		free(history_block);
	}
}


// void	aux_heredoc(char *delimiter, int tmp_fd, int *i, t_token *parsed_list)
// {
// 	char	*line;
// 	char	*history_block;

// 	line = NULL;
// 	history_block = NULL;
// 	init_history_block(&history_block, delimiter);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strcmp(line, delimiter) == 0)
// 		{
// 			if (line)
// 				*i = 1;
// 			break ;
// 		}
// 		update_history(line, &history_block);
// 		write_to_temp_file(tmp_fd, line, delimiter, parsed_list);
// 	}
// 	if (*i == 1)
// 		update_history(delimiter, &history_block);
// 	if (history_block)
// 	{
// 		add_history(history_block);
// 		free(history_block);
// 	}
// }

char	*m_get_delimiter_lexeme(t_token *parsed_list)
{
	t_token	*current;

	current = parsed_list;
	while (current)
	{
		if (current->type == DELIMITER)
		{
			ft_printf("DELIMITER: %s\n", current->lexeme); // ----- debug
			if (current->quote == 0)
				ft_printf("expandir in heredoc: %s\n", current->lexeme); // ----- debug
			else
				ft_printf("não expandir in heredoc: %s\n", current->lexeme); // ----- debug
			return (current->lexeme);
		}
		current = current->next;
	}
	return (NULL);
}
