#include "../includes/tokenizer.h"

int	m_is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '$');
}

void	m_skip_whitespace(char *input, int *i)
{
	while (input[*i] && isspace(input[*i]))
		(*i)++;
}

t_token	*m_tokenize(t_token **tokens, char *input)
{
	int		i;
	// char	*lexeme;

	i = 0;
	while (input[i])
	{
		m_skip_whitespace(input, &i);
		if (m_is_special_char(input[i]))
		{
			m_add_token(tokens, m_create_token(input[i], OPERATOR));
			i++;
		}
		else if (input[i])
		{
			m_add_token(tokens, m_create_token(input[i], WORD));
			i++;
		}
	}
	return (*tokens);
}
