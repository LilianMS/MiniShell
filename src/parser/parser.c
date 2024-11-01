#include "../includes/parser.h"

t_token *m_create_cmd_token(t_token *start, int command_len)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->lexeme = lexeme;
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
		if (aux_list->type == WORD)
		{
			start = aux_list;
			while (aux_list->type == WORD)
			{
				aux_list = aux_list->next;
				command_len++;
			}
			if (command_len > 0)
				m_add_token(parsed_list, m_create_cmd_token(start, command_len));
		}
		else
			m_add_token(parsed_list, aux_list);
		aux_list = aux_list->next;
	}
	return (parsed_list);
}
	//criar função que lê os nós de palavras 
	//e coloca os valores em um nó só, em um array de arrays

	//criar estrutura com o tipo de nó COMMAND e outros tipos de nós possíveis (VARIABLE, STRING) -> COLOCAR COMMAND, VARIABLE E STRING NOS ENUMS