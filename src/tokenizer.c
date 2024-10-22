#include "../includes/tokenizer.h"

// int	m_is_special_char(char c)
// {
// 	return (c == '|' || c == '<' || c == '>' || c == '$');
// }

// void	m_skip_whitespace(char *input, int *i)
// {
// 	while (input[*i] && isspace(input[*i]))
// 		(*i)++;
// }

int	m_get_next_status(int status, int str_index)
{
	if(status == 1)

}

t_token	*m_tokenize(t_token **tokens, char *input)
{
	t_automat	aut;

	ft_bzero(&aut, sizeof(t_automat));
	aut.str_len = ft_strlen(input);
	aut.status = 1;
	while (aut.i <= aut.str_len)
	{
		aut.status = m_get_next_status(aut.status, input[aut.i]);
		if (aut.status != 1)
			aut.lexeme_len++;
		if (aut.status == -1)
		{
			m_free_tokens(tokens);
			break;
		}
		if (m_is_final_status(aut.status))
			m_get_token(&aut, tokens, input);
		aut.i++;
	}
	return (*tokens);
}
