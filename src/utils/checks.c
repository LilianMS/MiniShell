#include "../../includes/minishell.h"

static int	ft_check_quotes(const char *line)
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

static int	check_invalid_chars(const char *line)
{
	const char	*invalid_chars = "();\\";

	while (*invalid_chars)
	{
		if (ft_strchr(line, *invalid_chars))
			return (1);
		invalid_chars++;
	}
	return (0);
}

int	m_check_line_input(const char *line)
{
	if (!ft_check_quotes(line))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", 2);
		return (0);
	}
	if (check_invalid_chars(line))
	{
		ft_putendl_fd("minishell: syntax error with invalid characters", 2);
		return (0);
	}
	return (1);
}

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
