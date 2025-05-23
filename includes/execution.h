#ifndef EXECUTION_H
# define EXECUTION_H

// Libs
# include "minishell.h"
# include "parser.h"
# include "tokenizer.h"
# include "builtin.h"
# include "ast.h"

//Structs
typedef struct s_mini		t_mini;
typedef struct s_token		t_token;
typedef struct s_redir		t_redir;
typedef struct s_env		t_env;

// Estrutura para guardar os file descriptors originais
struct s_redir
{
	int	stdin_backup;
	int	stdout_backup;
	int	stderr_backup;
	int	current_fd;
};

//Functions
int		m_find_directory(char *cmd);
int		m_execution(t_tree *node, t_mini *mini);
int		m_simple_command(t_tree *node, t_mini *mini);
int		m_execute_command(char **tree_node_cmd, t_mini *mini);
char	*m_create_path(char *cmd_path, char **node_cmd, char **env);
char	**m_env_list_to_array(t_env *env_list);
int		m_handle_redir(t_tree *node, t_mini *mini, t_redir *redir_fd);
t_tree	*m_find_command_node(t_tree *node);
int		m_execute_all_redirs(t_redir *redir_fd, t_tree *node);
void	m_init_redirect(t_redir *redir_fd);
void	m_restore_redirect(t_redir *redir_fd);
int		m_handle_pipe(t_tree *node, t_mini *mini);
void	m_free_everything(t_mini *mini);
int		m_exec_redir_command(t_tree *node, t_mini *mini);
int		m_check_permissions(char *cmd_path);
int		m_sort_status(int status);
int		m_validate_path(char *cmd_path, char **node_cmd, char **env);
int		m_empty_cmd(void);
void	m_close_fds(t_mini *mini);
pid_t	m_get_process_id();
int		m_is_absolute_path(char *cmd_path);
char	**m_remove_empty_strings(char **cmd_array);
char	**m_find_env_paths(char **envp);
int		m_prepare_command(char **tree_node_cmd, char ***cleaned_cmd_array, t_mini *mini);

#endif
