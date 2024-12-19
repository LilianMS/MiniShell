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

void	write_to_temp_file(int temp_fd, char *line)
{
	write(temp_fd, line, strlen(line));
	write(temp_fd, "\n", 1);
	free(line);
}

void	aux_heredoc(char *delimiter, int temp_fd, int *i)
{
	char	*line;
	char	*history_block;

	line = NULL;
	history_block = NULL;
	init_history_block(&history_block, delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				*i = 1;
			break ;
		}
		update_history(line, &history_block);
		write_to_temp_file(temp_fd, line);
	}
	if (*i == 1)
		update_history(delimiter, &history_block);
	if (history_block)
	{
		add_history(history_block);
		free(history_block);
	}
}

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
