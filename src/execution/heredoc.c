#include "../../includes/minishell.h"

int	create_temp_file(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		perror("Error creating temp file");
	return (fd);
}

void	m_heredoc(t_token **parsed_list)
{
	char	*delimiter;
	int		temp_fd;
	int		i;

	i = 0;
	delimiter = m_get_delimiter_lexeme(*parsed_list);
	if (!delimiter)
	{
		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
		return ;
	}
	temp_fd = create_temp_file();
	if (temp_fd == -1)
		return ;
	aux_heredoc(delimiter, temp_fd, &i);
	close(temp_fd);
	if (i == 0)
		ft_printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s'\n", delimiter);
	unlink(".heredoc_tmp");
	ft_printf("heredoc: exec?\n"); // ---debug
}
