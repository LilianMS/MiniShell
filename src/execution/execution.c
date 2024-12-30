#include "../../includes/minishell.h"

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
	int exit_status;

	pid = 0;
	exit_status = 0;
	if (mini->tree->type == COMMAND)
	{
		if (m_is_builtin(mini->tree) != -1)
			exit_status = m_execute_builtin(mini, parsed_list);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				exit_status = m_execute_command(mini->tree->command, mini->env_list);
				// TRANSFORMAR AS LINHAS ABAIXO EM UMA FUNÇÃO ÚNICA
				m_free_env_list(mini->env_list);
				m_free_tokens(parsed_list);
				m_tree_cleaner(mini->tree);
				exit(mini->exit_status);
			}
			else
			{
				waitpid(pid, &mini->exit_status, 0);
				exit_status = WEXITSTATUS(mini->exit_status);
			}
		}
	}
	return (exit_status);
}

int	m_close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
	return (-1);
}

// int	m_execute_command_2(t_tree *tree, t_minishell *data)
// {
// 	int		args_num;
// 	int		ret_code;

// 	ret_code = 0;
// 	args_num = token_list_size(tree->command);
// 	if (args_num != 0)
// 	{
// 		ret_code = exec_execve(tree, data);
// 		close(STDIN_FILENO);
// 		close(STDOUT_FILENO);
// 		close(STDERR_FILENO);
// 	}
// 	return (ret_code);
// }

int	m_execute_redir(t_mini *mini)
{
	int		exit_status;

	exit_status = 0; //mudar para receber o código certo
	ft_printf("filename = %s\n\n", mini->tree->right->content);
	if (mini->tree->type == REDIR_OUT)
		mini->fd = open(mini->tree->right->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		mini->fd = -1;
	if (mini->fd == -1)
	{
		perror(mini->tree->right->content);
		return (1);
	}
	dup2(mini->fd, STDOUT_FILENO);
	mini->fd = m_close_fd(mini->fd);
	// close(STDIN_FILENO);
	close(STDOUT_FILENO);
	// close(STDERR_FILENO);
	return (exit_status);
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
		mini->exit_status = m_execute_redir(mini);
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

