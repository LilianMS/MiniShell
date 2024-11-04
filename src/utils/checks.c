#include "../../includes/minishell.h"

int	ft_check_quotes(const char *line)
{
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	while (*line)
	{
		if (*line == '\'' && !double_q)
			single_q = !single_q;
		else if (*line == '\"' && !single_q)
			double_q = !double_q;
		line++;
	}
	return (!single_q && !double_q);
}

// -- função para limpar as aspas em qualquer caso
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