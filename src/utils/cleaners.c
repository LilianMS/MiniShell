#include "../../includes/minishell.h"

char	ft_is_quotes_type(char *lexeme, int *start, int *end)
{
	char	id_quote;
	int		i;

	id_quote = 0;
	i = 0;
	while (lexeme[i])
	{
		if ((lexeme[i] == '\'' || lexeme[i] == '\"') && id_quote == 0)
		{
			id_quote = lexeme[i];
			*start = i;
		}
		else if (lexeme[i] == id_quote)
		{
			*end = i;
			return (id_quote);
		}
		i++;
	}
	*start = -1;
	*end = -1;
	return (0);
}

// char	*m_clean_quotes(char *lexeme)
// {
// 	char	id_quote;
// 	int		start;
// 	int		end;
// 	char	*new_lexeme;

// 	id_quote = ft_is_quotes_type(lexeme, &start, &end);
// 	if (!id_quote) // Sem aspas
// 		return (ft_strdup(lexeme));
// 	new_lexeme = ft_substr(lexeme, start + 1, end - start - 1); // Extrai sem aspas
// 	free(lexeme); // Libera original
// 	return (new_lexeme);
// }


// -- função para limpar as aspas nos casos do minishell
char	*m_clean_quotes(char *lexeme)
{
	char	id_quote;
	char	*new_lexeme;
	int		start;
	int		end;
	int		i;

	start = -1;
	end = -1;
	id_quote = ft_is_quotes_type(lexeme, &start, &end);
	if (id_quote)
	{
		new_lexeme = malloc(sizeof(char) * ((ft_strlen(lexeme) - 2) + 1));
		i = 0;
		while (lexeme[i])
		{
			if (i != start && i != end)
				*new_lexeme++ = lexeme[i];
			i++;
		}
		*new_lexeme = '\0';
		new_lexeme -= (ft_strlen(lexeme) - 2); // Volta o ponteiro para o início / reduz linhas rs
		free(lexeme);
		return (new_lexeme);
	}
	return (lexeme);
}
