#include "../../includes/minishell.h"

void	print_heredoc_message(t_hdoc *hdoc)
{
	char	*message[2];

	message[0] = "minishell: warning: ";
	message[1] = "here-document delimited by end-of-file (wanted `";
	ft_putstr_fd(message[0], STDERR_FILENO);
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
	strcpy(filename, "/tmp/heredoc");
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

char	*m_heredoc_get_delimiter(t_tree *node)
{
	if (node == NULL || node->right == NULL)
		return (NULL);
	if (node->right->type == DELIMITER)
		return (node->right->content);
	return (NULL);
}

void	m_heredoc_update_node(t_tree **node, t_hdoc *hdoc)
{
	if ((*node)->right->type == DELIMITER \
		&& ft_strcmp((*node)->right->content, hdoc->delimiter) == 0)
	{
		free((*node)->right->content);
		(*node)->right->content = ft_strdup(hdoc->filename);
		ft_printf("node->right->content: %s\n", (*node)->right->content); // ---debug
		// (*node)->right->type = FILENAME;
		// ft_printf("node->right->type: %d\n", (*node)->right->type); // ---debug
	}
}

void	m_sig_heredoc(int signal __attribute__((unused)))
{
	g_signal_status = 128 + SIGINT;
	ft_putendl_fd("", STDOUT_FILENO);
	close(STDIN_FILENO);
}

void	heredoc_signals(void)
{
	signal(SIGINT, m_sig_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

int	m_init_heredoc(t_hdoc *hdoc, t_tree *node)
{
	if (!hdoc)
	{
		perror("Error: hdoc is not initialized");
		return (1);
	}
	hdoc->exit_flag = 0;
	hdoc->delimiter = m_heredoc_get_delimiter(node);
	if (!hdoc->delimiter)
	{
		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
		return (1);
	}
	hdoc->temp_fd = heredoc_create_file(&hdoc);
	if (hdoc->temp_fd == -1)
		return (1);
	heredoc_signals();
	return (0);
}

int	m_heredoc(t_tree *node, t_mini *mini)
{
	t_hdoc	*hdoc;

	hdoc = mini->hdoc;
	if (m_init_heredoc(hdoc, node))
		return (1);
	ft_printf("hdoc->delimiter: %s\n", hdoc->delimiter); // ---debug
	m_aux_heredoc(hdoc, node, mini);
	if (hdoc->exit_flag == 1)
		print_heredoc_message(hdoc);
	if (hdoc->exit_flag == 0 && g_signal_status != 130)
		m_heredoc_update_node(&node, hdoc);
	close(hdoc->temp_fd);
	ft_printf("heredoc: exec?\n"); // ---debug
	m_exec_signals(1);
	return (0);
}
