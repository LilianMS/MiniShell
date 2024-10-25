#include "../includes/tokenizer.h"

int	m_is_special_char(char c)
{
	return (c == '|' || \
			c == '<' || c == '>' || \
			c == '\'' || c == '\"');
}


int	m_get_token_type(int status)
{
	if (status == 41)
		return (PIPE);
	else if (status == 62)
		return (REDIR_IN);
	else if (status == 61)
		return (REDIR_HEREDOC);
	else if (status == 72)
		return (REDIR_OUT);
	else if (status == 71)
		return (REDIR_APPEND);
	else if (status == 83)
		return (WORD);
	else
		return (UNKNOWN);
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

int	m_get_next_status(int status, char c)
{
	int	new_status;

	if(status == 1)
		new_status = m_get_status_1(c);
	else if (status == 40)
		new_status = m_get_status_40(c);
	else if (status == 60)
		new_status = m_get_status_60(c);
	else if (status == 70)
		new_status = m_get_status_70(c);
	else if (status == 80)
		new_status = m_get_status_80(c);
	else if (status == 81)
		new_status = m_get_status_81(c);
	else if (status == 82)
		new_status = m_get_status_82(c);
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
