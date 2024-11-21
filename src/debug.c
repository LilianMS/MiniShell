#include "../includes/debug.h"

// --debug
void	print_tokens(t_token **tokens)
{
	t_token	*current = *tokens;
	int		i = 0;

	while (current)
	{
		ft_printf("Token %i: %s (Type: %d)\n", i++, current->lexeme, current->type);
		current = current->next;
	}
}

// --debug
void	print_parsed_tokens(t_token **tokens)
{
	t_token *current = *tokens;
	int i = 0;
	int x = 0;

	while (current)
	{
		x = 0;
		if (current->type == COMMAND)
		{
			while(x < current->command_len)
			{
				ft_printf("Parsed Token %i: %s (Type: %d)\n", i, current->command[x], current->type);
				x++;
			}
		}
		else
			ft_printf("Parsed Token %i: %s (Type: %d)\n", i, current->lexeme, current->type);
		i++;
		current = current->next;
	}
}

// --debug -- substituida pela builtin m_env
void	print_env_list(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp) {
		printf("Name: %s, Value: %s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

// --debug testes de comandos builtin
// abaixo:
// m_exit (in progress)
// m_env (ok)
// ft_echo (ok)
// ft_pwd (ok)
// m_export (in progress)

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

int	m_exit(t_mini *mini)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	m_free_env_list(mini->env_list);
	rl_clear_history();
	exit(0);
}

int	ft_echo(char **args)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (args[i] && i >= 1)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}

int		ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}

//// export

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

/// fim export

// unset

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

// fim unset

// função para testar comandos builtin
void	ft_debug_tests(t_mini *mini)
{
	if (ft_strcmp(mini->line, "exit") == 0)
	{
		m_exit(mini);
	}
	if (ft_strcmp(mini->line, "env") == 0)
	{
		m_env(mini->env_list);
	}
	if (ft_strncmp(mini->line, "echo", 4) == 0)
	{
		char **split = ft_split(mini->line, ' ');
		// ft_printf("split[0]: %s\n", split[0]); // debug
		ft_echo(split);
		ft_free_split(split);
	}
	if (ft_strcmp(mini->line, "pwd") == 0)
	{
		ft_pwd();
	}
	if (ft_strncmp(mini->line, "export", 6) == 0)
	{
		char **split = ft_split(mini->line, ' ');
		if (split[1])
			m_export(split, mini->env_list);
		ft_free_split(split);
		m_env(mini->env_list);
	}
	if (ft_strncmp(mini->line, "unset", 5) == 0)
	{
		char **split = ft_split(mini->line, ' ');
		if (split[1])
			m_unset(split, mini->env_list);
		ft_free_split(split);
		m_env(mini->env_list);
	}
}
