#include "../../includes/minishell.h"

void	m_sig_heredoc(int signal __attribute__((unused)))
{
	g_signal_status = 128 + SIGINT;
	m_update_nb_lines(1);
	ft_putendl_fd("", STDOUT_FILENO);
	close(STDIN_FILENO);
}

void	heredoc_signals(void)
{
	signal(SIGINT, m_sig_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	print_heredoc_message(t_hdoc *hdoc)
{
	char	*message[2];

	message[0] = "minishell: warning: here-document at line ";
	message[1] = "delimited by end-of-file (wanted `";
	ft_putstr_fd(message[0], STDERR_FILENO);
	ft_putnbr_fd(hdoc->nb_line_del, STDERR_FILENO);
	ft_putstr_fd(message[1], STDERR_FILENO);
	ft_putstr_fd(hdoc->delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

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
	strcpy(filename, "heredoc");
	strcat(filename, suffix);
	free(suffix);
	fd = ft_create_file(filename);
	if (fd != -1)
		((*hdoc)->suffix_doc)++;
	if ((*hdoc)->filename)
		free((*hdoc)->filename);
	(*hdoc)->filename = ft_strdup(filename);
	return (fd);
}
