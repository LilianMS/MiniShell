#include "../includes/parser.h"

// --- funções para m_quotes_and_expansion


// Expansão de `$$`: PID do processo
		// pid_t	m_get_pid(void);
// Expansão de `$?`: Código de saída
	// global g_signal_status
// Expansão de `$n`: Argumentos posicionais ou vazio

int	m_is_special_cases_dollar(char *lexeme)
{
	char	*dollar_position;

	dollar_position = ft_strchr(lexeme, '$');
	if (!dollar_position)
		return (0);
	if (ft_strncmp(dollar_position, "$$", 2) == 0
		|| ft_strncmp(dollar_position, "$?", 2) == 0)
		return (1);
	if (dollar_position[1] && ft_isdigit(dollar_position[1]))
		return (1);
	return (0);
}

// static void	m_expansion_special_cases(char **expansion, char **remaining_text, \
// 	char *temp_cleaned_lexeme)
// {
// 	if (ft_strncmp(temp_cleaned_lexeme, "$$", 2) == 0)
// 	{
// 		*expansion = ft_itoa(m_get_pid());
// 		*remaining_text = ft_strdup(temp_cleaned_lexeme + 2);
// 	}
// 	else if (ft_strncmp(temp_cleaned_lexeme, "$?", 2) == 0)
// 	{
// 		*expansion = ft_itoa(g_signal_status);
// 		*remaining_text = ft_strdup(temp_cleaned_lexeme + 2);
// 	}
// 	else if (temp_cleaned_lexeme[0] == '$' && ft_isdigit(temp_cleaned_lexeme[1]))
// 	{
// 		*expansion = ft_strdup("");
// 		*remaining_text = ft_strdup(temp_cleaned_lexeme + 2);
// 	}
// }
/*
int m_is_dollar_outside_single_quotes(char *str, int *index)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == '\'')
        {
            m_skip_quotes(str, &i); // Ignora trecho dentro de aspas simples
            continue;
        }
        if (str[i] == '$')
        {
            *index = i;
            return (1);
        }
        i++;
    }
    *index = -1;
    return (0);
}


char **m_split_dollar(char *str)
{
	char	**pieces;
	// int		start;
	// int		end;
	// int		dollar_index;
	// int		piece_index;

	pieces = ft_calloc(ft_strlen(str) + 1, sizeof(char *)); // Espaço suficiente
	int start = 0, end = 0, dollar_index, piece_index = 0;

	while (m_is_dollar_outside_single_quotes(&str[end], &dollar_index))
	{
		dollar_index += end;
		if (dollar_index > start)
			pieces[piece_index++] = ft_substr(str, start, dollar_index - start); // Texto antes de `$`
		start = dollar_index;
		end = start + 1;
	}
	if (start < ft_strlen(str))
		pieces[piece_index] = ft_strdup(&str[start]); // Último pedaço
	return (pieces);
}
*/


// char	*m_get_expand_string(char *lexeme, t_env *env_list)
// {
// 	char	*temp_cleaned_lexeme;
// 	char	*cleaned_lexeme;
// 	char	*result;
// 	char	*expansion;
// 	char	*remaining_text;

// 	temp_cleaned_lexeme = m_clean_quotes(lexeme);
// 	if (m_is_special_cases_dollar(temp_cleaned_lexeme))
// 		m_expansion_special_cases(&expansion, &remaining_text, temp_cleaned_lexeme);
// 	else
// 	{
// 		cleaned_lexeme = m_clean_dollar(temp_cleaned_lexeme);
// 		if (m_get_env(env_list, cleaned_lexeme))
// 			expansion = ft_strdup(m_get_env(env_list, cleaned_lexeme));
// 		else
// 			expansion = ft_strdup("");
// 		free(cleaned_lexeme);
// 		remaining_text = ft_strdup("");
// 	}
// 	if (temp_cleaned_lexeme)
// 		free(temp_cleaned_lexeme);
// 	result = ft_strjoin(expansion, remaining_text);
// 	if (expansion)
// 		free(expansion);
// 	if (remaining_text)
// 		free(remaining_text);
// 	return (result);
// }


// char	*m_get_expand_string(char *lexeme, t_env *env_list)
// {
// 	char	*cleaned_lexeme;
// 	char	*temp_cleaned_lexeme;
// 	char	*value;
// 	char	*empty_string;

// 	temp_cleaned_lexeme = m_clean_quotes(lexeme);
// 	cleaned_lexeme = m_clean_dollar(temp_cleaned_lexeme);
// 	value = m_get_env(env_list, cleaned_lexeme);
// 	free(cleaned_lexeme);
// 	if (value)
// 		return (ft_strdup(value));
// 	else
// 	{
// 		empty_string = malloc(1);
// 		if (empty_string)
// 			empty_string[0] = '\0';
// 		return (empty_string);
// 	}
// }

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
	int i = 0;
	int n = 0;

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
	return (result);
}

// static char	*m_expansion_special_cases(char *temp_lexeme)
// {
// 	char	*before;
// 	char	*expansion;
// 	char	*remaining_text;
// 	char	*result;
// 	char	*dollar_position;

// 	dollar_position = ft_strchr(temp_lexeme, '$');
// 	before = ft_substr(temp_lexeme, 0, dollar_position - temp_lexeme);
// 	if (ft_strncmp(dollar_position, "$$", 2) == 0)
// 	{
// 		expansion = ft_itoa(m_get_pid());
// 		remaining_text = ft_strdup(dollar_position + 2);
// 	}
// 	else if (ft_strncmp(dollar_position, "$?", 2) == 0)
// 	{
// 		expansion = ft_itoa(g_signal_status);
// 		remaining_text = ft_strdup(dollar_position + 2);
// 	}
// 	else if (dollar_position[1] && ft_isdigit(dollar_position[1]))
// 	{
// 		expansion = ft_strdup("");
// 		remaining_text = ft_strdup(dollar_position + 2);
// 	}
// 	result = ft_strjoin(before, expansion);
// 	result = ft_strjoin_free(result, remaining_text);
// 	free(before);
// 	free(expansion);
// 	free(remaining_text);
// 	return (result);
// }

static char	*m_expansion_special_cases(char *dollar_position)
{
	char	*expansion;

	if (ft_strncmp(dollar_position, "$$", 2) == 0)
		expansion = ft_itoa(m_get_pid());
	else if (ft_strncmp(dollar_position, "$?", 2) == 0)
		expansion = ft_itoa(g_signal_status);
	else if (dollar_position[1] && ft_isdigit(dollar_position[1]))
		expansion = ft_strdup("");
	else
		expansion = ft_strdup("$"); // Caso especial não identificado, retorna o próprio $
	return (expansion);
}

char	*m_get_expand_string(char *lexeme, t_env *env_list)
{
	char	*temp_cleaned_lexeme;
	char	*before_dollar;
	char	*expansion;
	char	*remaining_text;
	char	*result;
	char	*dollar_position;
	char	*cleaned_lexeme;

	remaining_text = NULL;
	temp_cleaned_lexeme = m_clean_quotes(lexeme);
	dollar_position = ft_strchr(temp_cleaned_lexeme, '$');
	if (!dollar_position) // Caso não haja $, retorna a string limpa
		return (temp_cleaned_lexeme);
	before_dollar = ft_substr(temp_cleaned_lexeme, 0, dollar_position - temp_cleaned_lexeme);
	if (m_is_special_cases_dollar(dollar_position))
	{
		expansion = m_expansion_special_cases(dollar_position);
		remaining_text = ft_strdup(dollar_position + 2);
	}
	else
	{
		cleaned_lexeme = m_clean_dollar(dollar_position);
		if (m_get_env(env_list, cleaned_lexeme))
			expansion = ft_strdup(m_get_env(env_list, cleaned_lexeme));
		else
			expansion = ft_strdup("");
		free(cleaned_lexeme);
		if (ft_strchr(dollar_position, '\''))
		{
			remaining_text = ft_strdup("\'");
		}
	}
	if (before_dollar)
	{
		result = ft_strjoin(before_dollar, expansion);
		if (remaining_text)
			result = ft_strjoin_free(result, remaining_text);
	}
	else if(remaining_text)
	{
		result = ft_strjoin(expansion, remaining_text);
	}
	else
	{
		result = ft_strdup(expansion);
	}
	free(temp_cleaned_lexeme);
	free(before_dollar);
	free(expansion);
	free(remaining_text);
	return (result);
}


// char	*m_get_expand_string(char *lexeme, t_env *env_list)
// {
// 	char	*temp_cleaned_lexeme;
// 	char	*cleaned_lexeme;
// 	char	*result;

// 	temp_cleaned_lexeme = m_clean_quotes(lexeme);
// 	if (m_is_special_cases_dollar(temp_cleaned_lexeme))
// 		result = m_expansion_special_cases(temp_cleaned_lexeme);
// 	else
// 	{
// 		cleaned_lexeme = m_clean_dollar(temp_cleaned_lexeme);
// 		if (m_get_env(env_list, cleaned_lexeme))
// 			result = ft_strdup(m_get_env(env_list, cleaned_lexeme));
// 		else
// 			result = ft_strdup("");
// 		free(cleaned_lexeme);
// 	}
// 	if (temp_cleaned_lexeme)
// 		free(temp_cleaned_lexeme);
// 	return (result);
// }

char	*m_quotes_and_expansion(char *lexeme, t_env *env_list)
{
	int	is_expand;

	is_expand = m_check_expand(lexeme);
	if (is_expand)
	{
		if (is_expand == 2)
			return (m_clean_quotes(lexeme));
		return (m_get_expand_string(lexeme, env_list));
	}
	return (m_clean_quotes(lexeme));
	
	// if (m_check_expand(lexeme))
	// 	return (m_get_expand_string(lexeme, env_list));
	// return (m_clean_quotes(lexeme));
}
