#include "../../includes/minishell.h"

char	*m_find_executable_path(char *cmd_path, char **node_cmd, char **env_paths)
{
	char	*path;
	int		i;

	i = 0;
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
	return (NULL);
}

char	*m_create_path(char *cmd_path, char **node_cmd, char **env)
{
	char	**env_paths;

	if (m_find_directory(node_cmd[0]))
		return (ft_strdup(node_cmd[0]));
	else
	{
		env_paths = m_find_env_paths(env);
		if (env_paths == NULL)
			return (ft_strdup(node_cmd[0]));
		cmd_path = m_find_executable_path(cmd_path, node_cmd, env_paths);
		if (cmd_path)
			return (cmd_path);
	}
	free_cmd_array(env_paths);
	return (NULL);
}
