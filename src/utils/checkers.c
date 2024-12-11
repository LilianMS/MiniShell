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

static int	is_quoted(char c, char *quote)
{
	if (*quote == '\0' && (c == '\'' || c == '\"'))
		*quote = c; // Inicia um contexto de aspas
	else if (*quote == c)
		*quote = '\0'; // Fecha o contexto de aspas
	return (*quote != '\0'); // Retorna se estamos dentro de aspas
}

int	check_invalid_chars(const char *input)
{
	const char	*invalid_chars = "();\\&";
	char		quote;

	quote = '\0'; // Rastreamos se estamos dentro de aspas
	while (*input)
	{
		if (is_quoted(*input, &quote))
		{
			input++; // Ignore os caracteres dentro das aspas
			continue ;
		}
		if (ft_strchr(invalid_chars, *input))
			return (1); // Encontrou um caractere inválido fora das aspas
		if (ft_strchr("|", *input))
		{
			if (*(input + 1) == '|')
				return (1); // Encontrou um caractere inválido fora das aspas
		}
		input++;
	}
	return (0); // Nenhum caractere inválido fora das aspas
}

int	m_check_line_input(const char *line)
{
	if (line == NULL || *line == '\0')
		return (0);
	else
		add_history(line);
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

int	m_is_input_null(t_mini *mini)
{
	if (!mini->line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (1);
	}
	return (0);
}
