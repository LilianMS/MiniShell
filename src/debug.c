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
