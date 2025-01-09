#include "../../includes/minishell.h"

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

