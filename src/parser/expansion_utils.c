#include "../includes/parser.h"

// função para expadir $$
pid_t	m_get_pid(void)
{
	return (8888);
}

// Expansão de `$$`: PID do processo
		// pid_t	m_get_pid(void);
// Expansão de `$?`: Código de saída
	// global g_signal_status
// Expansão de `$n`: Argumentos posicionais ou vazio

int	m_is_special_cases_dollar(char *lexeme)
{
	if (ft_strncmp(lexeme, "$$", 2) == 0 || ft_strncmp(lexeme, "$?", 2) == 0)
		return (1);
	if (lexeme[0] == '$' && ft_isdigit(lexeme[1]))
		return (1);
	return (0);
}

void	m_expansion_special_cases(char **expansion, char **remaining_text, \
	char *temp_cleaned_lexeme)
{
	if (ft_strncmp(temp_cleaned_lexeme, "$$", 2) == 0)
	{
		*expansion = ft_itoa(m_get_pid());
		*remaining_text = ft_strdup(temp_cleaned_lexeme + 2);
	}
	else if (ft_strncmp(temp_cleaned_lexeme, "$?", 2) == 0)
	{
		*expansion = ft_itoa(g_signal_status);
		*remaining_text = ft_strdup(temp_cleaned_lexeme + 2);
	}
	else if (temp_cleaned_lexeme[0] == '$' && ft_isdigit(temp_cleaned_lexeme[1]))
	{
		*expansion = ft_strdup("");
		*remaining_text = ft_strdup(temp_cleaned_lexeme + 2);
	}
}
