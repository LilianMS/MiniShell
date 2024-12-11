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

void	aux_heredoc(const char *delimiter, int temp_fd)
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
		ft_replace_chr(buffer, '\n', '\0');
		if (ft_strcmp(buffer, delimiter) == 0)
			break ;
		write(temp_fd, buffer, ft_strlen(buffer));
		write(temp_fd, "\n", 1);
	}
}

void	m_heredoc(t_token *parsed_list)
{
	const char	*delimiter;
	int			temp_fd;

	delimiter = m_get_delimiter_lexeme(parsed_list);
	if (!delimiter)
	{
		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
		return ;
	}
	// delimiter = args[1];
	temp_fd = create_temp_file();
	if (temp_fd == -1)
		return ;
	aux_heredoc(delimiter, temp_fd);
	if (dup2(temp_fd, STDIN_FILENO) == -1)
	{
		perror("Error redirecting stdin");
		close(temp_fd);
		return ;
	}
	close(temp_fd); // Fechar o arquivo temporário
	ft_printf("heredoc: exec?\n"); // ---debug
}
