#ifndef PARSER_H
# define PARSER_H

// Libs
# include "minishell.h"
# include "tokenizer.h"
# include "debug.h"
# include "ast.h"

// Structs
typedef struct s_env_parse	t_env_parse;
typedef struct s_env		t_env;

struct s_env_parse
{
	char					*equal_sign;
	char					*name;
	char					*value;
	int						name_len;
};

struct s_env
{
	char					*name;
	char					*value;
	struct s_env			*prev;
	struct s_env			*next;
};

// Functions

char	*m_quotes_and_expansion(char *lexeme, t_env *env_list);
char	*m_get_env(t_env *env_list, const char *var_name);
void	m_free_env_list(t_env *env_list);
t_env	*m_create_env_list(char **envp);
t_env	*m_create_env_node(char *name, char *value);
void	m_add_node_env(t_env **head, t_env *new_node);

pid_t	m_get_pid(void); // função para expadir $$ -- não implementada
// função para setar e pegar o status do sinal ao chamar $?
char	*m_set_get_status(int code_exit);
char	*m_clean_dollar(char *str, int *idx);
char	*m_get_expand_string(char *lexeme, t_env *env_list);
char	*ft_strjoin_free(char *s1, char *s2);
int		m_is_special_cases_dollar(char *lexeme);
char	*m_expansion_special_cases(char *dollar_position);
char	*m_process_after_dollar(char *dollar_position, t_env *env_list);

char	ft_is_quotes_type(char *lexeme, int *start, int *end);
char	**split_by_quotes(char *input);

#endif