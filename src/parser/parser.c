#include "../includes/parser.h"

t_token *m_parse_tokens(t_token **token_list, t_token **parsed_list)
{
	t_token	*aux_list;
	int		i = 0;
	// int		start = 0;
	int		command_len = 0;

	aux_list = *token_list;
	while (aux_list->type == WORD)
	{
		command_len++;
		aux_list++;
	}
	
}
	//criar função que lê os nós de palavras 
	//e coloca os valores em um nó só, em um array de arrays

	//criar estrutura com o tipo de nó COMMAND e outros tipos de nós possíveis (VARIABLE, STRING) -> COLOCAR COMMAND, VARIABLE E STRING NOS ENUMS