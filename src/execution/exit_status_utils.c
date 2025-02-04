#include "../../includes/minishell.h"

int	m_sort_status(int status)
{
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status == SIGINT)
			return (130);
		else if (status == SIGQUIT)
		{
			signal(SIGPIPE, SIG_IGN);
			ft_putstr_fd("Quit: (core dumped)\n", STDERR_FILENO);
			return (SIGQUIT + 128);
		}
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}