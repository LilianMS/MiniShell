#include "../includes/minishell.h"

int	m_env(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp && temp->next != NULL)
	{
		ft_printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	if (temp)
		ft_printf("%s=%s\n", temp->name, temp->value);
	return (0);
}
