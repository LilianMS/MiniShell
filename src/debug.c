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
}