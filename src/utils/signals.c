#include "../../includes/minishell.h"

void	m_init_signals(void)
{
	signal(SIGINT, m_sig_int);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	update_mini(t_mini *mini)
{
	// if (g_signal_status == 130)
	// 	m_update_num_lines(mini);
	g_signal_status = 0;
	m_init_signals();
	dup2(mini->backup_fd_in, STDIN_FILENO);
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->term);
	m_exec_signals(1);
	// m_update_num_lines(mini);
}

void	m_sig_int(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_status = 128 + signum;
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	m_sig(int signum)
{
	(void)signum;
	g_signal_status = 130;
	ft_putendl_fd("", STDOUT_FILENO);
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
