#include "../includes/minishell.h"

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
	return (*name != NULL);
}

static void	exp_update_or_add_env(t_env **env_list, char *name, char *value)
{
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			if (value)
			{
				free(temp->value);
				temp->value = ft_strdup(value);
				break ;
			}
			else
				return ;
		}
		temp = temp->next;
	}
	m_add_node_env(env_list, m_create_env_node(name, value));
}

int	m_export(char **args, t_env *env_list)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	while (args[i])
	{
		name = NULL;
		value = NULL;
		if (!exp_parse_input(args[i], &name, &value) || !exp_is_valid_name(name))
		{
			free(name);
			free(value);
			ft_printf("export: `%s`: not a valid identifier\n", args[i]); // mudar para função m_print_error
		}
		else
			exp_update_or_add_env(&env_list, name, value);
		free(name);
		free(value);
		i++;
	}
	return (0);
}

/*
 - primeiraversão sem leaks, mas sem validação de input

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
		new_env = m_create_env_node(split[0], split[1]);
		m_add_node_env(&env_list, new_env);
		i++;
	}
	ft_free_split(split);
	return (0);
}
*/

/* melhorando...
int m_export(char **args, t_env *env_list)
{
	char    **split;
	int     i;
	t_env   *temp;
	t_env   *new_env;

	i = 1;
	while (args[i])
	{
		split = ft_split(args[i], '=');
		if (!split[0])
		{
			ft_free_split(split);
			return (-1);
		}
		temp = env_list;
		while (temp)
		{
			if (ft_strcmp(temp->name, split[0]) == 0)
			{
				free(temp->value);
				temp->value = ft_strdup(split[1]);
				ft_free_split(split);
				break;
			}
			temp = temp->next;
		}
		if (!temp)
		{
			new_env = m_create_env_node(split[0], split[1]);
			m_add_node_env(&env_list, new_env);
		}
		ft_free_split(split);
		i++;
	}
	return (0);
}
*/
