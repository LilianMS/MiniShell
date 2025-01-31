#include "../../includes/minishell.h"

int	m_execute_command(char **tree_node_cmd, t_mini *mini)
{
	int		status;
	char	*cmd_path;
	char	**env;

	status = 0;
	cmd_path = NULL;
	if (tree_node_cmd[0][0] == '\0')
		return (m_empty_cmd());
	env = m_env_list_to_array(mini->env_list);
	cmd_path = m_create_path(cmd_path, tree_node_cmd, env);
	status = m_validate_path(cmd_path, tree_node_cmd, env);
	if (status)
	{
		// m_close_fds(mini);
		return (status);
	}
	else
	{
		if (execve(cmd_path, tree_node_cmd, env))
		{
			status = m_check_permissions(cmd_path);
			free(cmd_path);
			free_cmd_array(env);
			// m_close_fds(mini);
			return (status);
		}
	}
	return (status);
}

int	m_sort_status(int status)
{
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status == SIGINT)
			return (130);
		else if (status == SIGQUIT)
		{
			signal(SIGPIPE, SIG_IGN);
			ft_putstr_fd("Quit: (core dumped)\n", STDERR_FILENO);
			return (SIGQUIT + 128);
		}
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	m_simple_command(t_tree *node, t_mini *mini)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = -1;
	pid = fork();
	m_exec_signals(pid);
	if (pid == 0)
	{
		mini->current_pid = m_get_process_id();
		status = m_execute_command(node->command, mini);
		m_free_everything(mini);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (m_sort_status(status));
	}
	return (status);
}

int	m_exec_redir_command(t_tree *node, t_mini *mini)
{
	int	status;

	if (m_is_builtin(node) != -1)
	{
		status = m_execute_builtin(node, mini);
		ft_putendl_fd("minishell: builtin execution error", STDERR_FILENO);
		m_free_everything(mini);
		exit(status);
	}
	else
	{
		status = m_execute_command(node->command, mini);
		exit(status);
	}
	return (status);
}

int	m_execution(t_tree *node, t_mini *mini)
{
	t_redir	redir_fd;
	int		exit_status;

	exit_status = 0;
	ft_bzero(&redir_fd, sizeof(t_redir));
	if ((node->type == COMMAND && m_is_builtin(node) == -1) && !node->parent)
		exit_status = m_simple_command(node, mini);
	else if (node->type == COMMAND && m_is_builtin(node) != -1)
		exit_status = m_execute_builtin(node, mini);
	else if (node->type == COMMAND)
		exit_status = m_execute_command(node->command, mini);
	else if (m_is_redir(node->type))
		exit_status = m_handle_redir(node, mini, &redir_fd);
	else if (node->type == PIPE)
		exit_status = m_handle_pipe(node, mini);
	if (g_signal_status == 130)
		exit_status = 130;
	return (exit_status);
}
