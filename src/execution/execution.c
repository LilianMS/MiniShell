#include "../../includes/minishell.h"

// Função para inicializar os backups dos fds
void m_init_redirect(t_redir *redir_fd)
{
    redir_fd->stdin_backup = dup(STDIN_FILENO);
    redir_fd->stdout_backup = dup(STDOUT_FILENO);
    redir_fd->stderr_backup = dup(STDERR_FILENO);
	redir_fd->current_fd = -1;
}

// Função para restaurar os fds originais
void m_restore_redirect(t_redir *redir_fd)
{
    dup2(redir_fd->stdin_backup, STDIN_FILENO);
    dup2(redir_fd->stdout_backup, STDOUT_FILENO);
    dup2(redir_fd->stderr_backup, STDERR_FILENO);
    close(redir_fd->stdin_backup);
    close(redir_fd->stdout_backup);
    close(redir_fd->stderr_backup);
}

void	m_free_everything(t_mini *mini, t_token **parsed_list)
{
	m_free_env_list(mini->env_list);
	m_free_tokens(parsed_list);
	m_tree_cleaner(mini->tree);
}

int m_check_cmd(char *cmd_path)
{
	int exit_status;

	exit_status = 0;
	if (access(cmd_path, F_OK) == -1)
		exit_status = 127;
	else if (access(cmd_path, F_OK | X_OK) == -1)
		exit_status = 126;
	return (exit_status);
}

int m_execute_command(char **tree_node_cmd, t_env *env_list)
{
	char *cmd_path;
	char **env;

	cmd_path = NULL;
	env = m_env_list_to_array(env_list);
	if (!env)
		return (1);
	cmd_path = m_create_path(cmd_path, tree_node_cmd, env);
	if (cmd_path == NULL)
	{
		free(cmd_path);
		free_cmd_array(env);
		return (127);
	}
	execve(cmd_path, tree_node_cmd, env);
	free(cmd_path);
	free_cmd_array(env);
	return (1);
}

int	m_simple_command(t_mini *mini, t_token **parsed_list)
{
	int pid;

	pid = 0;
	if (mini->tree->type == COMMAND)
	{
		if (m_is_builtin(mini->tree) != -1)
			mini->exit_status = m_execute_builtin(mini, parsed_list);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				mini->exit_status = m_execute_command(mini->tree->command, mini->env_list);
				m_free_everything(mini, parsed_list);
				exit(mini->exit_status);
			}
			else
			{
				waitpid(pid, &mini->exit_status, 0);
				mini->exit_status = WEXITSTATUS(mini->exit_status);
			}
		}
	}
	return (mini->exit_status);
}

int	m_close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
	return (1);
}

int	m_execute_redir_in(t_mini *mini, t_redir *redir_fd)
{
	if (mini->tree->type == REDIR_IN)
		redir_fd->current_fd = open(mini->tree->right->content, O_RDONLY);
	if (redir_fd->current_fd == -1)
	{
		perror("minishell: input redirection");
		m_restore_redirect(redir_fd);
		return (1);
	}
	if(dup2(redir_fd->current_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		close(redir_fd->current_fd);
		m_restore_redirect(redir_fd);
		return (1);
	}
	close(redir_fd->current_fd);
	return (0);
}

int	m_execute_redir_out_append(t_mini *mini, t_redir *redir_fd)
{
	if (mini->tree->type == REDIR_OUT)
		redir_fd->current_fd = open(mini->tree->right->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mini->tree->type == REDIR_APPEND)
		redir_fd->current_fd = open(mini->tree->right->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir_fd->current_fd == -1)
	{
		perror("minishell: output redirection");
		m_restore_redirect(redir_fd);
		return (1);
	}
	if(dup2(redir_fd->current_fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		close(redir_fd->current_fd);
		m_restore_redirect(redir_fd);
		return (1);
	}
	close(redir_fd->current_fd);
	return (0);
}

t_tree	*m_find_command_node(t_tree *node)
{
	while (node && node->type != COMMAND)
			node = node->left;
	return (node);
}

int	m_execute_all_redirs(t_mini*mini, t_redir *redir_fd, t_tree *node)
{
	t_tree *current;

	m_init_redirect(redir_fd);
	current = node;
	while (current && m_is_redir(current->type))
	{
		if (current->type == REDIR_IN)
			m_execute_redir_in(mini, redir_fd);
		else if (current->type == REDIR_OUT)
			m_execute_redir_out_append(mini, redir_fd);
		else if (current->type == REDIR_APPEND)
			m_execute_redir_out_append(mini, redir_fd);
		current = current->left;
	}
	return (0);
}

int	m_handle_redir(t_mini *mini, t_redir *redir_fd, t_token **parsed_list)
{
	t_tree	*original_root;
	t_tree	*cmd_node;
	int		status;

	status = 0;
	original_root = mini->tree;
	if (m_execute_all_redirs(mini, redir_fd, mini->tree))
		return (1);
	cmd_node = m_find_command_node(mini->tree);
	if (!cmd_node)
	{
		m_restore_redirect(redir_fd);
		return (1);
	}
	mini->tree = cmd_node;
	status = m_simple_command(mini, parsed_list);
	m_restore_redirect(redir_fd);
	mini->tree = original_root;
	return (status);
}

void	m_execution(t_mini *mini, t_token **parsed_list)
{
	t_redir redir_fd;

	ft_bzero(&redir_fd, sizeof(t_redir));
	if (!mini->tree)
		mini->exit_status = 1;
	if (mini->tree->type == COMMAND)
		mini->exit_status = m_simple_command(mini, parsed_list);
	else if (m_is_redir(mini->tree->type))
		mini->exit_status = m_handle_redir(mini, &redir_fd, parsed_list);
	// else if (mini->tree->type == PIPE)
	// 	mini->exit_status = m_exec_pipe(mini, parsed_list);
	m_tree_cleaner(mini->tree);
	m_free_tokens(parsed_list);
	// else
	// {
	// 	m_execution(tree->left);
	// 	m_execution(tree->right);
	// }
	// close_fds();
}

