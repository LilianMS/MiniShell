#include "../includes/parser.h"

// --debug
void	print_env_list(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp) {
		printf("Name: %s, Value: %s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

// criar nó de variável de ambiente
t_env	*m_create_env_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

