#include "../includes/debug.h"

int	list_size(t_token **parsed_list)
{
	int list_size;
	t_token *curr;

	list_size = 0;
	curr = *parsed_list;
	while (curr)
	{
		curr = curr->next;
		list_size++;
	}
	return (list_size);
}

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
	t_token *curr = *tokens;
	int position = 0;
	int x = 0;

	while (curr)
	{
		x = 0;
		if (curr->type == COMMAND)
		{
			while(x < curr->command_len)
			{
				fprintf(stderr, "| %8d | %13s | %4d | %2p | %2p | %2p |\n", \
					position, curr->command[x], curr->type, curr->prev, curr, curr->next);
				// ft_printf("Parsed Token %i: %s (Type: %d)\n", position, current->command[x], current->type);
				x++;
			}
		}
		else
			fprintf(stderr, "| %8d | %13s | %4d | %2p | %2p | %2p |\n", \
				position, curr->lexeme, curr->type, curr->prev, curr, curr->next);
			// ft_printf("Parsed Token %i: %s (Type: %d)\n", position, current->lexeme, current->type);
		position++;
		curr = curr->next;
	}
}

void	list_printer(t_token **parsed_list)
{
	int		parsed_list_len;
	t_token	*curr;

	curr = *parsed_list;
	parsed_list_len = list_size(parsed_list);
	fprintf(stderr, "List size: %d\n", parsed_list_len);
	fprintf(stderr, "List content:\n");
	fprintf(stderr, "|-----|---------------|------|----------------|----------------|----------------|\n");
	fprintf(stderr, "| pos |    content    | type |      prev      |      curr      |      next      |\n");
	fprintf(stderr, "|-----|---------------|------|----------------|----------------|----------------|\n");
	print_parsed_tokens(parsed_list);
	fprintf(stderr, "|-----|---------------|------|----------------|----------------|----------------|\n\n");
	fflush(stderr);
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
