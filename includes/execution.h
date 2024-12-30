#ifndef EXECUTION_H
#define EXECUTION_H

// Libs
#include "minishell.h"
#include "parser.h"
#include "tokenizer.h"
#include "debug.h"
#include "ast.h"

//Structs
typedef struct s_mini		t_mini;
typedef struct s_token		t_token;

//Functions
void     m_execution(t_mini *mini, t_token **parsed_list);
int		m_execute_command(char **tree_node_cmd, t_env *env_list);
char	*m_create_path(char *cmd_path, char **node_cmd, char **envp);
char	**m_env_list_to_array(t_env *env_list);
int		m_check_cmd(char *cmd_path);

#endif