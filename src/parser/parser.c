#include "../includes/parser.h"

char	**m_populate_cmd_array(t_token *start, int command_len)
{
	int		i;
	char	**command;
	// OBSERVAÇÃO!!!!!!!!!!!!
	// EXPANDIR ASPAS AQUI DENTRO!!!!
	// E DOLAR SIGN TAMBÉM!!!!!!
	// NÃO ESQUECER!!! (ง'̀-'́)ง
	// ┬┴┬┴┤ ͜ʖ ͡°) ├┬┴┬┴
	i = 0;
	command = malloc(sizeof(char *) * command_len + 1);
	while(i <= command_len)
	{
		command[i] = ft_strdup(start->lexeme);
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
	if (!token)
		return (NULL);
	token->command = m_populate_cmd_array(start, command_len);
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
	return (*parsed_list);
}
	//criar função que lê os nós de palavras 
	//e coloca os valores em um nó só, em um array de arrays

	//criar estrutura com o tipo de nó COMMAND e outros tipos de nós possíveis (VARIABLE, STRING) -> COLOCAR COMMAND, VARIABLE E STRING NOS ENUMS