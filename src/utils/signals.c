#include "../../includes/minishell.h"

char	*m_get_exit_status(void)
{
	return (ft_itoa(g_signal_status));
}

void	m_update_exit_status(int code_exit)
{
	if (code_exit >= 0)
		g_signal_status = code_exit;
}

void	m_sig(int signum)
{
	(void)signum;
	g_signal_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	m_exec_signals(int pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
	}
	else if (pid == 1)
	{
		signal(SIGINT, m_sig_int);
		signal(SIGPIPE, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, m_sig);
		signal(SIGPIPE, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
