#include "../../includes/minishell.h"

void	m_free_everything(t_mini *mini)
{
	if (mini->line)
		free(mini->line);
	if (mini->env_list)
		m_free_env_list(mini->env_list);
	if (mini->tree)
		m_tree_cleaner(mini->tree);
	if (mini->hdoc->filename)
		free(mini->hdoc->filename);
	if (mini->hdoc)
		free(mini->hdoc);
	m_close_fds(mini);
}

int	m_check_permissions(char *cmd_path)
{
	if (access(cmd_path, X_OK) == -1 \
	|| access(cmd_path, R_OK | W_OK) == -1)
	{
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
		ft_putendl_fd(cmd_path, STDERR_FILENO);
		return (126);
	}
	return (0);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (-1);
	return (S_ISDIR(statbuf.st_mode));
}

int	m_empty_cmd(void)
{
	ft_putendl_fd("minishell: command not found: ''", STDERR_FILENO);
	return (127);
}

int	m_validate_path(char *cmd_path, char **node_cmd, char **env)
{
	(void)env;
	if (cmd_path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(node_cmd[0], STDERR_FILENO);
		free_cmd_array(env);
		return (127);
	}
	else if (cmd_path == node_cmd[0] && access(cmd_path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(node_cmd[0], STDERR_FILENO);
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
		free_cmd_array(env);
		return (127);
	}
	else if (is_directory(cmd_path) == 1 \
			&& m_check_permissions(cmd_path) == 126)
	{
		// free_cmd_array(env);
		return (126);
	}
	else if (is_directory(cmd_path) == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putendl_fd(": is a directory", STDERR_FILENO);
		free_cmd_array(env);
		return (126);
	}
	return (0);
}
