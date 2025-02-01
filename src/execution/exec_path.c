#include "../../includes/minishell.h"

static char	**m_find_env_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (envp[i] && envp[i][4] != '\0' \
		&& envp[i][5] != '\0')
	{
		paths = ft_split(envp[i] + 5, ':');
		return (paths);
	}
	return (NULL);
}

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

static int	env_list_size(t_env *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	return (i);
}

char	**m_env_list_to_array(t_env *env_list)
{
	char	**envp;
	char	*tmp_str;
	int		i;

	i = env_list_size(env_list);
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_list)
	{
		envp[i] = ft_strjoin(env_list->name, "=");
		tmp_str = envp[i];
		if (env_list->value)
		{
			envp[i] = ft_strjoin(envp[i], env_list->value);
			free(tmp_str);
		}
		env_list = env_list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
