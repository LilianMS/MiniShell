#include "../../includes/minishell.h"

char	**m_find_env_paths(char **envp)
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
