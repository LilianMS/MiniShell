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

char	*m_clean_dollar(char *str)
{
	char	*new_str;
	int		i;
	int		n;

	n = 0;
	while (str[i])
	{
		if (str[i] == '$')
			n++;
	}
	if (strchr(str, '$'))
	{
		new_str = malloc(sizeof(char) * ((ft_strlen(str) - n) + 1));
		i = 0;
		while (str[i])
		{
			if (str[i] != '$')
				*new_str++ = str[i];
			i++;
		}
		*new_str = '\0';
		new_str -= (ft_strlen(str) - 1);
		free(str);
		return (new_str);
	}
	return (str);
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
	free(temp_cleaned_lexeme);
	result = ft_strjoin(expansion, remaining_text);
	free(expansion);
	free(remaining_text);
	return (result);
}

char	*m_quotes_and_expansion(char *lexeme, t_env *env_list)
{
	if (m_check_expand(lexeme))
		return (m_get_expand_string(lexeme, env_list));
	return (m_clean_quotes(lexeme));
}
