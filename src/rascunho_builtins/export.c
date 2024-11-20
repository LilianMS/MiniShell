#include "../includes/minishell.h"

int	m_export(char **args, t_env *env_list)
{
	char	**split;
	int		i;
	t_env	*temp;
	t_env	*new_env;

	i = 1;
	while (args[i])
	{
		split = ft_split(args[i], '=');
		temp = env_list;
		while (temp)
		{
			if (ft_strncmp(temp->name, split[0], ft_strlen(split[0])) == 0)
			{
				temp->value = ft_strdup(split[1]);
				ft_free_split(split);
				return (0);
			}
			temp = temp->next;
		}
		new_env = m_create_env_node(ft_strdup(split[0]), ft_strdup(split[1]));
		m_add_node_env(&env_list, new_env);
		i++;
	}
	ft_free_split(split);
	m_free_env_list(temp);
	return (0);
}
