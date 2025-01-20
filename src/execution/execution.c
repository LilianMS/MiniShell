#include "../../includes/minishell.h"

void	m_free_everything(t_mini *mini)
{
	if (mini->line)
		free(mini->line);
	if (mini->env_list)
		m_free_env_list(mini->env_list);
	if (mini->tree)
		m_tree_cleaner(mini->tree);
}

int m_check_cmd(char *cmd_path)
{
	int status;

	status = 0;
	if (access(cmd_path, F_OK) == -1)
		status = 127;
	else if (access(cmd_path, F_OK | X_OK) == -1)
		status = 126;
	return (status);
}

int m_execute_command(char **tree_node_cmd, t_mini *mini)
{
	//SEPARAR ESSA PARTE EM OUTRA FUNÇÃO
	char *cmd_path;
	char **env;

	cmd_path = NULL;
	env = m_env_list_to_array(mini->env_list);
	if (!env)
		return (1);
	cmd_path = m_create_path(cmd_path, tree_node_cmd, env);
	if (cmd_path == NULL)
	{
		free(cmd_path);
		free_cmd_array(env);
		return (127);
	}
	//SEPARAR ESSA PARTE EM OUTRA FUNÇÃO
	execve(cmd_path, tree_node_cmd, env);
	free(cmd_path);
	free_cmd_array(env);
	return (1);
}

int	m_simple_command(t_tree *node, t_mini *mini)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = -1;
		pid = fork();
		if (pid == 0)
		{
			status = m_execute_command(node->command, mini);
			// msg d erro
			m_free_everything(mini);
			exit(status);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
		}
	return (status);
}

int	m_exec_redir_command(t_tree *node, t_mini *mini)
{
	int	status;

	if (m_is_builtin(node) != -1)
	{
		status = m_execute_builtin(node, mini);
		perror("minishell: builtin execution error");
		m_free_everything(mini);
		exit(status);
	}
	else
	{
		status = m_execute_command(node->command, mini);
		perror("minishell: external command execution error");
		m_free_everything(mini);
		exit(status);
	}
	return (status);
}

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
	m_free_everything(mini);
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
		perror("minishell: pipe error");
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
	if (m_is_builtin(node) != -1)
		mini->exit_status = m_execute_builtin(node, mini);
	else if (node->type == COMMAND && !node->parent)
		mini->exit_status = m_simple_command(node, mini);
	else if (node->type == COMMAND)
		mini->exit_status = m_execute_command(node->command, mini);
	else if (m_is_redir(node->type))
		mini->exit_status = m_handle_redir(node, mini, &redir_fd);
	else if (node->type == PIPE)
		mini->exit_status = m_handle_pipe(node, mini);
	
}


