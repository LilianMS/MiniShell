#include "../includes/builtin.h"

int	m_exit(t_mini **mini, t_token **parsed_list)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	m_free_env_list((*mini)->env_list);
	m_free_tokens(parsed_list);
	m_tree_cleaner((*mini)->tree);
	m_heredoc_delete_files(*mini);
	free((*mini)->hdoc);
	rl_clear_history();
	exit(0);
}
