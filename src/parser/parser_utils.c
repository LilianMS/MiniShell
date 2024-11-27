#include "../includes/parser.h"

// --- funções para m_quotes_and_expansion
char	ft_is_qt_type(char *lexeme)
{
	char	id_quote;
	int		i;

	id_quote = 0;
	i = 0;
	while (lexeme[i])
	{
		if ((lexeme[i] == '\'' || lexeme[i] == '\"') && id_quote == 0)
			id_quote = lexeme[i];
		else if (lexeme[i] == id_quote)
			return (id_quote);
		i++;
	}
	return (0);
}

int	m_qntd_dollar(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '$')
			n++;
		i++;
	}
	return (n);
}

int	m_check_expand(char *lexeme)
{
	char	id_quote;
	int		n_dollar;

	id_quote = ft_is_qt_type(lexeme);
	if (ft_strchr(lexeme, '$') && (id_quote == '\"' || id_quote == 0))
	// if (ft_strchr(lexeme, '$') && (id_quote == '\"' || id_quote == 0 || id_quote == '\''))
	{
		n_dollar = m_qntd_dollar(lexeme);
		if (n_dollar > 1 && !(m_is_special_cases_dollar(lexeme)))
			return (1);
		else if ((lexeme[0] == '$' && lexeme[1] == '\0')
			|| lexeme[2] == '\"' || lexeme[2] == ' ')
			return (0);
		return (1);
	}
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (result);
}

char	*m_quotes_and_expansion(char *lexeme, t_env *env_list)
{
	int	is_expand;

	is_expand = m_check_expand(lexeme);
	if (is_expand)
	{
		if (is_expand == 2)
			return (m_clean_quotes(lexeme)); // ----- temporário
		return (m_get_expand_string(lexeme, env_list));
	}
	return (m_clean_quotes(lexeme));
}
