#include "../includes/minishell.h"

int	m_exit(t_mini *mini)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	m_free_env_list(mini->env_list);
	exit(0);
}
