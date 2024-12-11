#include "../includes/builtin.h"

void	m_print_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
}

int	exp_is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0] || ft_isdigit(name[0]) || name[0] == '=')
		return (0);
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	exp_parse_input(char *arg, char **name, char **value)
{
	char	*equal_pos;

	if (!arg || !arg[0])
		return (0);
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		*name = ft_substr(arg, 0, equal_pos - arg);
		*value = ft_strdup(equal_pos + 1);
	}
	else
	{
		*name = ft_strdup(arg);
		*value = NULL;
	}
	return (0);
}

void	exp_update_or_add_env(t_env **env_list, char *name, char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->value)
				free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			return;
		}
		current = current->next;
	}
	new_node = m_create_env_node(name, value);
	m_add_node_env(env_list, new_node);
}

int m_export(t_env *env_list, char **args)
{
	char	*name;
	char	*value;
	int		i;

	i = 1;
	if (!args[1])
		m_print_sorted_env(env_list);
	else
	{
		while (args[i])
		{
			name = NULL;
			value = NULL;
			exp_parse_input(args[i], &name, &value);
			if (!exp_is_valid_name(name))
				m_print_error("export: `", args[i], "': not a valid identifier");
			else
                exp_update_or_add_env(&env_list, name, value);
			free(name);
			free(value);
			i++;
		}
	}
	return (0);
}
