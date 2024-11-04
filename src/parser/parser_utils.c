#include "../includes/parser.h"

// --- funções para m_quotes_and_expansion
int	m_check_expand(char *lexeme)
{
	int	str_len;

	str_len = ft_strlen(lexeme);
	if ((lexeme[0] == '\"') && (lexeme[1] == '$')
		&& (lexeme[str_len - 1] == '\"')
		&& (lexeme[2] != '\"') && (lexeme[2] != ' '))
		return (1);
	else if (lexeme[0] == '$' && lexeme[1] != '\0')
		return (1);
	else
		return (0);
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
	if (m_check_expand(lexeme))
		return (m_get_expand_string(lexeme));
	return (m_clean_quotes(lexeme));
}
