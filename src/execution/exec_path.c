#include "../../includes/minishell.h"

static char	**m_find_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (envp[i])
	{
		paths = ft_split(envp[i] + 5, ':');
		return (paths);
	}
	return (NULL);
}

int	m_check_permissions(char *cmd_path)
{
	if (access(cmd_path, X_OK) == -1 \
	|| access(cmd_path, R_OK | W_OK) == -1)
	{
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
		ft_putendl_fd(cmd_path, STDERR_FILENO);
		// ft_printf_fd(STDERR_FILENO, "permission denied\n");
		return (126);
	}
	return (1);
}

int	m_check_absolute_path(char *cmd_path)
{
	if (access(cmd_path, F_OK) == 0)
		return (0);
	return (1);
}

char	*m_create_path(char *cmd_path, char **node_cmd, char **env)
{
	char	*path;
	char	**env_paths;
	int		i;

	i = 0;
	if (m_check_absolute_path(node_cmd[0]) == 0)
		return (node_cmd[0]);
	else
	{
		env_paths = m_find_paths(env);
		while (env_paths[i])
		{
			path = ft_strjoin(env_paths[i++], "/");
			cmd_path = ft_strjoin(path, node_cmd[0]);
			free(path);
			if (access(cmd_path, F_OK) == 0)
			{
				free_cmd_array(env_paths);
				return (cmd_path);
			}
			free(cmd_path);
		}
	}
	free_cmd_array(env_paths);
	return (NULL);
}

static int env_list_size(t_env *env_list)
{
	int i;

	i = 0;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	return (i);
}

char **m_env_list_to_array(t_env *env_list)
{
	char **envp;
	char *tmp_str;
	int i;

	i = env_list_size(env_list);
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_list)
	{
		envp[i] = ft_strjoin(env_list->name, "=");
		tmp_str = envp[i];
		envp[i] = ft_strjoin(envp[i], env_list->value);
		free(tmp_str);
		env_list = env_list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	get_status(int exit_status)
{
	static int	status;

	if (exit_status != -1)
		status = exit_status;
	return (status);
}