#include "../includes/parser.h"

	// OBSERVAÇÃO!!!!!!!!!!!!
	// EXPANDIR ASPAS AQUI DENTRO!!!!
	// E DOLAR SIGN TAMBÉM!!!!!!
	// NÃO ESQUECER!!! (ง'̀-'́)ง
	// ┬┴┬┴┤ ͜ʖ ͡°) ├┬┴┬┴

char	*m_check_expansion(char	*lexeme)
{
	int		i;
	int		str_len;

	i = 0;
	if (lexeme[0] == '\"')
	{
		if (ft_strchr(lexeme, '$'))
		{
			//expansão de variável
			ft_printf("achou $");
		}
		else
			str_len = ft_strlen(lexeme) - 2;
	}
	else if (lexeme[0] == '\'')
		str_len = ft_strlen(lexeme) - 2;
	//memmove
	return (lexeme);
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
	//criar função que lê os nós de palavras 
	//e coloca os valores em um nó só, em um array de arrays

	//criar estrutura com o tipo de nó COMMAND e outros tipos de nós possíveis (VARIABLE, STRING) -> COLOCAR COMMAND, VARIABLE E STRING NOS ENUMS