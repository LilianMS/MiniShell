#include "../includes/builtin.h"

//TRATAR ERROS (SE RECEBER STRING OU MAIS DE 1 PARÂMETRO)
//PRECISA TRATAR LONG (LONG?) INT

int	m_exit(t_mini **mini)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	m_free_env_list((*mini)->env_list);
	// m_free_tokens(parsed_list);
	m_tree_cleaner((*mini)->tree);
	rl_clear_history();
	exit(0);
}
