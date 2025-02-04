#include "../../includes/minishell.h"

int	m_find_directory(char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp[i])
	{
		if (tmp[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	m_check_permissions(char *cmd_path)
{
	if (access(cmd_path, X_OK) != 0)
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
	if (cmd_path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(node_cmd[0], STDERR_FILENO);
		free_cmd_array(env);
		return (127);
	}
	else if (ft_strcmp(cmd_path, node_cmd[0]) == 0 \
				&& access(cmd_path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(node_cmd[0], STDERR_FILENO);
		ft_putendl_fd(": no such file or directory", STDERR_FILENO); free_cmd_array(env);
		return (127);
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
