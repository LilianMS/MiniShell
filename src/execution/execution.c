#include "../../includes/minishell.h"

// Função para inicializar os backups dos fds
void m_init_redirect(t_redir *redir_fd)
{
    redir_fd->stdin_backup = dup(STDIN_FILENO);
    redir_fd->stdout_backup = dup(STDOUT_FILENO);
    redir_fd->stderr_backup = dup(STDERR_FILENO);
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
	else if (access(cmd_path, X_OK) == -1)
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
	t_redir redir_fd;

	pid = 0;
	// if (mini->tree->type == COMMAND)
	// {
	if (m_is_builtin(mini->tree->left) != -1)
	{
		if (m_execute_redir(mini, &redir_fd)) 
			mini->exit_status = 1;
		else 
		{
			mini->exit_status = m_execute_builtin(mini, parsed_list);
			m_restore_redirect(&redir_fd);
		}
	}
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
	return (mini->exit_status);
}

int	m_close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
	return (-1);
}

int	m_execute_redir(t_mini *mini, t_redir *redir_fd)
{
	m_init_redirect(redir_fd);
	if (mini->tree->type == REDIR_OUT)
		mini->fd = open(mini->tree->right->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mini->fd == -1)
	{
		perror("minishell: output redirection");
		return (1);
	}
	if(dup2(mini->fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		close(mini->fd);
		return (1);
	}
	// close(STDIN_FILENO);
	close(mini->fd);
	// close(STDERR_FILENO);
	return (0);
}

void	m_execution(t_mini *mini, t_token **parsed_list)
{
	if (!mini->tree)
		mini->exit_status = 1;
	if (mini->tree->type == COMMAND \
		&& mini->tree->left == NULL \
		&& mini->tree->right == NULL)
		mini->exit_status = m_simple_command(mini, parsed_list);
	else if (mini->tree->type == REDIR_OUT \
		&& mini->tree->left->type == COMMAND \
		&& mini->tree->right->type == FILENAME)
		mini->exit_status = m_simple_command(mini, parsed_list);
	m_tree_cleaner(mini->tree);
	// m_free_env_list(mini->env_list);
	m_free_tokens(parsed_list);
	// else
	// {
	// 	m_execution(tree->left);
	// 	m_execution(tree->right);
	// }
	// close_fds();
}

