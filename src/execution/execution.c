#include "../../includes/minishell.h"

void	m_free_everything(t_mini *mini)
{
	m_free_env_list(mini->env_list);
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

int	m_simple_command(t_tree *node, t_mini *mini)
{
	pid_t pid;

	pid = 0;
	if (node->type == COMMAND)
	{
		if (m_is_builtin(mini->tree) != -1)
			mini->exit_status = m_execute_builtin(node, mini);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				mini->exit_status = m_execute_command(node->command, mini->env_list);
				m_free_everything(mini);
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

// t_tree *m_find_leftmost_pipe(t_tree *node)
// {
// 	t_tree *current;

// 	current = node;
// 	while (current && current->left && current->type == PIPE)
// 		current = current->left;
// 	if (current->type != PIPE)
// 		current = current->parent;
// 	ft_putendl_fd(current->content, STDERR_FILENO);			//	-->debug
// 	ft_putstr_fd(current->left->command[0], STDERR_FILENO); //	-->debug
// 	ft_putendl_fd("", STDERR_FILENO);						//				-->debug
// 	return (current);
// }

int	m_handle_fork_error(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (1);
}

int	m_children_process(int *pipefd, t_tree *node, int pid_index, t_mini *mini)
{
	if (pid_index == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	m_execution(node, mini);
	exit(mini->exit_status);
}

int	m_fork_and_exec(int *pipefd, t_tree *node, int pid_index, t_mini *mini)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	//função que captura/checa sinais
	if (pid == 0)
		m_children_process(pipefd, node, pid_index, mini);
	return (pid);
}

int	m_handle_pipe(t_tree *node, t_mini *mini)
{
	int		pipefd[2];
	int		status[2];
	pid_t	pid[2];

	if (!node || !node->left || !node->right)
		return (-1);
	if (pipe(pipefd) == -1)
	{
		ft_putendl_fd("pipe error", STDERR_FILENO);
		return (1);
	}
	pid[0] = m_fork_and_exec(pipefd, node->left, 0, mini);
	if (pid[0] < 0)
		return (m_handle_fork_error(pipefd));
	pid[1] = m_fork_and_exec(pipefd, node->right, 1, mini);
	if (pid[1] < 0)
		return (m_handle_fork_error(pipefd));
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	if (WIFEXITED(status[1]))
		status[1] = WEXITSTATUS(status[1]);
	return (status[1]);
}

void	m_execution(t_tree *node, t_mini *mini)
{
	t_redir	redir_fd;

	ft_bzero(&redir_fd, sizeof(t_redir));  
	// if (!mini->tree)
	// 	mini->exit_status = 1;
	if (mini->tree->type == COMMAND)
		mini->exit_status = m_simple_command(node, mini);
	else if (m_is_redir(node->type)) // arrumar para receber tree_node
		mini->exit_status = m_handle_redir(node, mini, &redir_fd);
	else if (node->type == PIPE)
		mini->exit_status = m_handle_pipe(node, mini);
	// if (tree_node->content)
	// {
	// 	int i = 0;
	// 	ft_putendl_fd(mini->tree->content, STDERR_FILENO);	//	-->debug
	// 	ft_putnbr_fd(i++, STDERR_FILENO); //	-->debug
	// 	ft_putendl_fd("", STDERR_FILENO);	//	-->debug
	// }
	m_tree_cleaner(mini->tree);
}


