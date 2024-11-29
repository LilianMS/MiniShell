#include "../includes/parser.h"

static char	*process_special_dollar(char **dollar_position)
{
	char	*expansion;

	expansion = m_expansion_special_cases(*dollar_position);
	*dollar_position += 2; // Avança 2 caracteres para pular o caso especial
	return (expansion);
}

static char	*process_regular_dollar(char **dollar_position, t_env *env_list)
{
	char	*cleaned_lexeme;
	char	*expansion;
	int		idx;

	cleaned_lexeme = m_clean_dollar(*dollar_position, &idx);
	if (m_get_env(env_list, cleaned_lexeme))
		expansion = ft_strdup(m_get_env(env_list, cleaned_lexeme));
	else
		expansion = ft_strdup("");
	free(cleaned_lexeme);
	*dollar_position += idx; // Avança o ponteiro para a próxima posição
	return (expansion);
}

static char	*add_text_before_next_dollar(char *result, char **dollar_position)
{
	char	*next_dollar;
	char	*text_before_next_dollar;
	char	*temp;

	next_dollar = ft_strchr(*dollar_position, '$');
	if (next_dollar)
	{
		text_before_next_dollar = ft_substr(*dollar_position, 0, next_dollar - *dollar_position);
		temp = ft_strjoin(result, text_before_next_dollar);
		free(text_before_next_dollar);
		*dollar_position = next_dollar;
	}
	else
	{
		temp = ft_strjoin(result, *dollar_position);
		*dollar_position = NULL;
	}
	return (temp);
}

// char	*m_process_after_dollar(char *dollar_position, t_env *env_list)
// {
// 	char	*result;
// 	char	*expansion;
// 	char	*temp;

// 	result = ft_strdup("");
// 	while (dollar_position)
// 	{
// 		if (m_is_special_cases_dollar(dollar_position))
// 			expansion = process_special_dollar(&dollar_position);
// 		else
// 			expansion = process_regular_dollar(&dollar_position, env_list);
// 		temp = ft_strjoin_free(result, expansion); // Usa join com free
// 		result = add_text_before_next_dollar(temp, &dollar_position);
// 	}
// 	return (result);
// }


char	*m_process_after_dollar(char *dollar_position, t_env *env_list)
{
	char	*result;
	char	*expansion;
	char	*temp;

	result = ft_strdup("");
	while (dollar_position)
	{
		if (m_is_special_cases_dollar(dollar_position))
			expansion = process_special_dollar(&dollar_position);
		else
			expansion = process_regular_dollar(&dollar_position, env_list);
		temp = ft_strjoin(result, expansion);
		free(result);
		free(expansion);
		result = add_text_before_next_dollar(temp, &dollar_position);
		free(temp);
	}
	return (result);
}
