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
typedef struct s_redir		t_redir;

// Estrutura para guardar os file descriptors originais
struct s_redir {
	int stdin_backup;
	int stdout_backup;
	int stderr_backup;
	int current_fd;
};

//Functions
void	m_execution(t_mini *mini, t_token **parsed_list);
int		m_execute_command(char **tree_node_cmd, t_env *env_list);
char	*m_create_path(char *cmd_path, char **node_cmd, char **envp);
char	**m_env_list_to_array(t_env *env_list);
int		m_check_cmd(char *cmd_path);
int		m_execute_redir(t_mini *mini, t_redir *redir_fd);
void	m_init_redirect(t_redir *redir_fd);
void	m_restore_redirect(t_redir *redir_fd);
int		m_handle_redir(t_mini *mini, t_redir *redir_fd, t_token **parsed_list);
void	m_init_redirect(t_redir *redir_fd);
void	m_restore_redirect(t_redir *redir_fd);
int		m_close_fd(int fd);
int		m_simple_command(t_mini *mini, t_token **parsed_list);

#endif