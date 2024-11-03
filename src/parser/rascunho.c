#include "../includes/parser.h"

int	m_check_expand(char *lexeme)
{
	if (ft_strchr(lexeme, '\"'))
		return (1);
	if (ft_strchr(lexeme, '\''))
		return (0);
	return (1);
}

char	*m_clean_quotes(char *lexeme)
{
	char	*new_lexeme;
	int		i;
	int		str_len;

	i = 0;
	str_len = ft_strlen(lexeme);
	if (((lexeme[0] == '\"') && (lexeme[str_len - 1] == '\"'))
		|| ((lexeme[0] == '\'') && (lexeme[str_len - 1] == '\'')))
	{
		str_len -= 2;
		new_lexeme = malloc(sizeof(char) * (str_len + 1));
		while (lexeme[i + 1])
		{
			new_lexeme[i] = lexeme[i + 1];
			i++;
		}
		new_lexeme[i - 1] = '\0';
		free(lexeme);
		return (new_lexeme);
	}
	return (lexeme);
}

// --- usando getenv temporariamente
char	*m_get_expand_string(char *lexeme)
{
	char	*cleaned_lexeme;
	char	*value;
	char	*empty_string;

	cleaned_lexeme = m_clean_quotes(lexeme);
	value = getenv(cleaned_lexeme);
	free(cleaned_lexeme);
	if (value)
		return (ft_strdup(value));
	else
	{
		empty_string = malloc(1);
		if (empty_string)
			empty_string[0] = '\0';
		return (empty_string);
	}
}

char	*m_quotes_and_expansion(char *lexeme)
{
	if (ft_strchr(lexeme, '$') && m_check_expand(lexeme))
		return (m_get_expand_string(lexeme));
	return (m_clean_quotes(lexeme));
}
