#include "../includes/parser.h"

// --- funções para m_quotes_and_expansion
int	m_check_expand(char *lexeme)
{
	int	str_len;

	str_len = ft_strlen(lexeme);
	// if ((lexeme[0] == '\"') && (ft_strchr(lexeme, '$'))
	// 	&& (lexeme[str_len - 1] == '\"')
	// 	&& (lexeme[2] != '\"') && (lexeme[2] != ' '))
	// 	return (1);
	// else if (lexeme[0] == '$' && lexeme[1] != '\0')
	// 	return (1);
	// else
	// 	return (0);

	if ((lexeme[0] == '\"') && (lexeme[1] == '$')
		&& (lexeme[str_len - 1] == '\"')
		&& (lexeme[2] != '\"') && (lexeme[2] != ' '))
		return (1);
	else if (lexeme[0] == '$' && lexeme[1] != '\0')
		return (1);
	else
		return (0);
}

// Expansão de `$$`: PID do processo
		// pid_t	m_get_pid(void);
// Expansão de `$?`: Código de saída
	// global g_signal_status
// Expansão de `$n`: Argumentos posicionais ou vazio

static int	m_is_special_cases_dollar(char *lexeme)
{
	if (ft_strncmp(lexeme, "$$", 2) == 0 || ft_strncmp(lexeme, "$?", 2) == 0)
		return (1);
	if (lexeme[0] == '$' && ft_isdigit(lexeme[1]))
		return (1);
	return (0);
}

static void	m_expansion_special_cases(char **expansion, char **remaining_text, \
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
// 	char	**split_lexeme;

// 	split_lexeme = m_split_dollar(lexeme);
// }

char	*m_get_expand_string(char *lexeme, t_env *env_list)
{
	char	*temp_cleaned_lexeme;
	char	*cleaned_lexeme;
	char	*result;
	char	*expansion;
	char	*remaining_text;

	temp_cleaned_lexeme = m_clean_quotes(lexeme);
	if (m_is_special_cases_dollar(temp_cleaned_lexeme))
		m_expansion_special_cases(&expansion, &remaining_text, temp_cleaned_lexeme);
	else
	{
		cleaned_lexeme = m_clean_dollar(temp_cleaned_lexeme);
		if (m_get_env(env_list, cleaned_lexeme))
			expansion = ft_strdup(m_get_env(env_list, cleaned_lexeme));
		else
			expansion = ft_strdup("");
		free(cleaned_lexeme);
		remaining_text = ft_strdup("");
	}
	if (temp_cleaned_lexeme)
		free(temp_cleaned_lexeme);
	result = ft_strjoin(expansion, remaining_text);
	if (expansion)
		free(expansion);
	if (remaining_text)
		free(remaining_text);
	return (result);
}


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


char	*m_quotes_and_expansion(char *lexeme, t_env *env_list)
{
	// if (ft_strchr(lexeme, '$'))
	// 	return (m_get_expand_string(lexeme, env_list));
	// return (m_clean_quotes(lexeme));
	
	if (m_check_expand(lexeme))
		return (m_get_expand_string(lexeme, env_list));
	return (m_clean_quotes(lexeme));
}
