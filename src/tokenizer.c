#include "../includes/tokenizer.h"

int	m_is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '$');
}


int	m_get_token_type(int status)
{
	if (status == 83)
		return (WORD);
	else
		return (OPERATOR);
}

void	m_get_new_token(t_automat *aut, t_token **token_list, char *input)
{
	t_token	*new_token;

	if(aut->status == 83) //substituir por validação via função "status need backtrack" e acrescentar todos os status na funçao
	{
		aut->lexeme_len--;
		aut->i--;
	}
	aut->token_type = m_get_token_type(aut->status);
	if (aut->token_type == WORD)
		aut->lexeme = ft_substr(input, (aut->i - (aut->lexeme_len - 1)), aut->lexeme_len);
	else
		aut->lexeme = NULL;
	new_token = m_create_token(aut->lexeme, aut->token_type);
	m_add_token(token_list, new_token);
	aut->lexeme_len = 0;
	aut->status = 1;
}

//LEGENDA STATUS
//---> 40 = PIPE
//---> 61 = REDIR_HEREDOC
//---> 62 = REDIR_IN
//---> 71 = REDIR_APPEND
//---> 72 = REDIR_OUT
//---> 83 = WORD
int	m_is_final_status(int status)
{
	return (status == 40 || \
			status == 61 || \
			status == 62 || \
			status == 71 || \
			status == 72 || \
			status == 83);
}

int	m_get_status_1(char c)
{
	if (ft_isalnum(c)) //ft_isalnum olha se é dígito ou alfabético
		return (80);
	else if (c == '|')
		return (100); //usando o número 100 para não esquecer de trocar depois
	else if (c == '<')
		return (100);
	else if (c == '>')
		return (100);
	else if (c == '$')
		return (100);
	else if (c == '\"')
		return (100);
	else if (c == '\'')
		return (100);
	else
		return (1);
}

int	m_get_status_80(char c)
{
	if (m_is_special_char(c) || c == ' ' || c == '\0')
		return (83);
	else
		return (80);
}

int	m_get_status_83(char str_index)
{
	if (str_index == '|')
		return (100);
	else if (str_index == '<')
		return (100);
	else if (str_index == '>')
		return (100);
	else if (str_index == '$')
		return (100);
	else
		return (1);
}

int	m_get_next_status(int status, char str_index)
{
	int	new_status;

	if(status == 1)
		new_status = m_get_status_1(str_index);
	else if (status == 80)
		new_status = m_get_status_80(str_index);
	else if (status == 83)
		new_status = m_get_status_83(str_index);
	else if (status == 100)
		return (100);
	else
		new_status = -1;
	return (new_status);
}

t_token	**m_tokenize(t_token **token_list, char *input)
{
	t_automat	aut;
	int			i = 0;

	ft_bzero(&aut, sizeof(t_automat));
	aut.str_len = ft_strlen(input);
	aut.status = 1;
	while (aut.i <= aut.str_len)
	{
		aut.status = m_get_next_status(aut.status, input[aut.i]);
		ft_printf("current status %i: %d\n", i++, aut.status); //debug pra saber se está capturando o status de forma certa
		if (aut.status != 1)
			aut.lexeme_len++;
		if (aut.status == -1)
		{
			m_free_tokens(token_list);
			break;
		}
		if (m_is_final_status(aut.status))
			m_get_new_token(&aut, token_list, input);
		aut.i++;
	}
	return (token_list);
}
