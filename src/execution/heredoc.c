#include "../../includes/minishell.h"

void	ft_replace_chr(char *str, char a, char replace)
{
	char	*is_char;

	is_char = strchr(str, a);
	if (is_char)
		*is_char = replace;
}

int	create_temp_file(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		perror("Error creating temp file");
	return (fd);
}

int	open_temp_file(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd == -1)
		perror("Error opening temp file");
	return (fd);
}

void	aux_heredoc(const char *delimiter, int temp_fd, int *i)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	while (1)
	{
		write(1, "> ", 2); // Exibir prompt
		bytes_read = read(0, buffer, sizeof(buffer) - 1); // Ler entrada do usuário
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		add_history(buffer);
		ft_replace_chr(buffer, '\n', '\0');
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			*i = 1;
			break ;
		}
		write(temp_fd, buffer, ft_strlen(buffer));
		write(temp_fd, "\n", 1);
	}
}

void	m_heredoc(t_token *parsed_list)
{
	const char	*delimiter;
	int			temp_fd;
	int			i;

	i = 0;
	delimiter = m_get_delimiter_lexeme(parsed_list);
	if (!delimiter)
	{
		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
		return ;
	}
	temp_fd = create_temp_file();
	if (temp_fd == -1)
		return ;
	aux_heredoc(delimiter, temp_fd, &i);
	close(temp_fd); // Fechar o arquivo temporário
	if (i == 0)
		ft_printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s'\n", delimiter);
	unlink(".heredoc_tmp");
	ft_printf("heredoc: exec?\n"); // ---debug
}


// bash não desabilita o sinal de controle C durante a execução do heredoc
// adicionar o conteúdo do arquivo temporário ao final da lista de argumentos



// void	aux_heredoc(const char *delimiter, int temp_fd)
// {
// 	char	buffer[1024];
// 	char	*history_block = NULL;
// 	char	*temp;
// 	ssize_t	bytes_read;

// 	history_block = ft_strjoin("<< ", delimiter);
// 	history_block = ft_strjoin(history_block, "\n");
// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		bytes_read = read(0, buffer, sizeof(buffer) - 1); // Ler entrada do usuário
// 		if (bytes_read <= 0)
// 			break;
// 		buffer[bytes_read] = '\0'; // Garantir que termina com '\0'
// 		ft_replace_chr(buffer, '\n', '\0');
// 		if (ft_strcmp(buffer, delimiter) == 0)
// 			break;
// 		write(temp_fd, buffer, ft_strlen(buffer));
// 		write(temp_fd, "\n", 1);
// 		temp = history_block;
// 		history_block = ft_strjoin(temp, buffer);
// 		history_block = ft_strjoin(history_block, "\n");
// 		free(temp);
// 		rl_replace_line(history_block, 0);
// 		rl_redisplay();
// 	}
// 	if (history_block)
// 		add_history(history_block);
// 	free(history_block);
// }
