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
