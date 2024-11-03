#include "../includes/parser.h"

char	*m_check_expansion(char	*lexeme)
{
	int		i;
	int		str_len;
	char	*new_lexeme;

	i = 0;
	if (lexeme[0] == '\"')
	{
		if (ft_strchr(lexeme, '$'))
		{
			//inserir função de expansão de variável
			ft_printf("\nachou $\n");
			str_len = ft_strlen(lexeme) - 2;
		}
		else
			str_len = ft_strlen(lexeme) - 2;
	}
	else if (lexeme[0] == '\'')
		str_len = ft_strlen(lexeme) - 2;
	new_lexeme = malloc(sizeof(char *) * str_len + 1);
	while(i < str_len)
	{
		new_lexeme[i] = lexeme[i + 1];
		i++;
	}
	new_lexeme[i] = '\0';
	printf("\nnew_lexeme =>> %s\n", new_lexeme);
	free(lexeme);
	return (new_lexeme);
}


void	m_copy_token(t_token **parsed_list, t_token *aux_token)
{
	t_token	*copy_token;

	copy_token = ft_calloc(sizeof(t_token), 1);
	copy_token->type = aux_token->type;
	m_add_token(parsed_list, copy_token);
}

char	**m_populate_cmd_array(t_token *start, int command_len)
{
	int		i;
	char	**command;
	i = 0;
	command = malloc(sizeof(char *) * (command_len + 1));
	if (!command)
		return NULL;
	while(i < command_len)
	{
		if (start && start->lexeme)
		{
			start->lexeme = m_check_expansion(start->lexeme);
			command[i] = ft_strdup(start->lexeme);
		}
		else
			command[i] = NULL;
		start = start->next;
		i++;
	}
	command[command_len] = NULL;
	return (command);
}

t_token *m_create_cmd_token(t_token *start, int command_len)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	ft_bzero(token, sizeof(t_token));
	if (!token)
		return (NULL);
	token->command = m_populate_cmd_array(start, command_len);
	token->command_len = command_len; // teste
	token->type = COMMAND;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token *m_parse_tokens(t_token **token_list, t_token **parsed_list)
{
	t_token	*aux_list;
	t_token	*start;
	int		command_len;

	start = NULL;
	command_len = 0;
	aux_list = *token_list;
	while (aux_list)
	{
		command_len = 0;
		if (aux_list->type == WORD)
		{
			start = aux_list;
			while (aux_list && aux_list->type == WORD)
			{
				aux_list = aux_list->next;
				command_len++;
			}
			if (command_len > 0 && start->lexeme)
				m_add_token(parsed_list, m_create_cmd_token(start, command_len));
		}
		else
		{
			m_copy_token(parsed_list, aux_list);
			aux_list = aux_list->next;
		}
	}
	return (*parsed_list);
}
