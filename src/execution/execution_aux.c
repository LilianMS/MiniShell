#include "../../includes/minishell.h"

int	m_handle_fork_error(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (1);
}

int	m_children_process(int *pipefd, t_tree *node, int pid_index, t_mini *mini)
{
	int	status;

	status = 0;
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
	status = m_execution(node, mini);
	m_free_everything(mini);
	exit(status);
}

int	m_fork_and_exec(int *pipefd, t_tree *node, int pid_index, t_mini *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	m_exec_signals(pid);
	if (pid == 0)
	{
		mini->current_pid = m_get_process_id();
		m_children_process(pipefd, node, pid_index, mini);
	}
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
		ft_putendl_fd("minishell: pipe error", STDERR_FILENO);
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
	status[1] = m_sort_status(status[1]);
	return (status[1]);
}
