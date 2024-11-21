#include "../includes/minishell.h"

// unset não precisa de validação apenas retorna 0 se não houver argumentos
// se houver argumentos remove os nós da lista de env

void	m_remove_node_env(t_env **env_list, char *name)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env_list;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				*env_list = temp->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	m_unset(char **args, t_env *env_list)
{
	int	i;

	i = 1;
	if (!args[i])
		return (0);
	while (args[i])
	{
		m_remove_node_env(&env_list, args[i]);
		i++;
	}
	return (0);
}
