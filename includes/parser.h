#ifndef PARSER_H
# define PARSER_H

// Libs
# include "minishell.h"

// Structs
typedef struct s_env_parse
{
	char	*equal_sign;
	char	*name;
	char	*value;
	int		name_len;
}	t_env_parse;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

// Functions
char	*m_quotes_and_expansion(char *lexeme);
char	*m_get_env(t_env *env_list, const char *var_name);
void	free_env_list(t_env *env_list);
t_env	*m_create_env_list(char **envp);

#endif