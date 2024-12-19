#ifndef BUILTIN_H
# define BUILTIN_H

//Libs
# include "minishell.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

enum e_builtin
{
	NO_BUILTIN,
	PWD,
	CD,
	ECHO,
	ENV,
	EXPORT,
	UNSET,
	EXIT
};

// functions builtins
int		ft_pwd(void);
int		ft_cd(char **args); // not implemented
int		ft_echo(char **args);
int		m_env(t_env *env_list);
int		m_export(t_env *env_list, char **args);
int		m_unset(t_env *env_list, char **args);
int		m_exit(t_mini **mini, t_token **parsed_list);
int		m_is_builtin(t_tree *tree_node);
int		m_execute_builtin(t_mini *mini, t_token **parsed_list);
void	m_print_sorted_env(t_env *env_list);

#endif