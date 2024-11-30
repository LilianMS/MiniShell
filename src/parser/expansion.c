#include "../includes/parser.h"

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

char	*m_expansion_special_cases(char *dollar_position)
{
	char	*expansion;

	if (ft_strncmp(dollar_position, "$$", 2) == 0)
		expansion = ft_itoa(m_get_pid());
	else if (ft_strncmp(dollar_position, "$?", 2) == 0)
		expansion = m_set_get_status(127); // 127 é o valor padrão para $? quando não há status -- o ultimo foi a execução de $?
	else if (dollar_position[1] && ft_isdigit(dollar_position[1]))
		expansion = ft_strdup("");
	else
		expansion = ft_strdup("$"); // Caso especial não identificado, retorna o próprio $
	return (expansion);
}

static char	*m_extract_before_dollar(char *lexeme)
{
	char	*dollar_position;
	char	*before_dollar;

	dollar_position = ft_strchr(lexeme, '$');
	if (!dollar_position)
		return (NULL);
	before_dollar = ft_substr(lexeme, 0, dollar_position - lexeme);
	return (before_dollar);
}

// char	*m_get_expand_string(char *lexeme, t_env *env_list)
// {
// 	char	*before_dollar;
// 	char	*processed_part;
// 	char	*result;
// 	char	*dollar_position;

// 	dollar_position = ft_strchr(lexeme, '$');
// 	if (!dollar_position) // Sem $
// 		return (ft_strdup(lexeme));
// 	before_dollar = m_extract_before_dollar(lexeme);
// 	processed_part = m_process_after_dollar(dollar_position, env_list);
// 	if (!before_dollar) // Garante que nunca seja nulo
// 		before_dollar = ft_strdup("");
// 	result = ft_strjoin_free(before_dollar, processed_part); // Usa join com free
// 	return (result);
// }


char	*m_get_expand_string(char *lexeme, t_env *env_list)
{
	char	*temp_cleaned_lexeme;
	char	*before_dollar;
	char	*processed_part;
	char	*result;
	char	*dollar_position;

	if (ft_strchr(lexeme, '\"'))
		temp_cleaned_lexeme = m_clean_quotes(lexeme);
	else
		temp_cleaned_lexeme = lexeme;
	dollar_position = ft_strchr(temp_cleaned_lexeme, '$');
	if (!dollar_position) // Sem $
		return (temp_cleaned_lexeme);
	before_dollar = m_extract_before_dollar(temp_cleaned_lexeme);
	processed_part = m_process_after_dollar(dollar_position, env_list);
	if (!before_dollar) // Garante que nunca seja nulo
		before_dollar = ft_strdup("");
	result = ft_strjoin(before_dollar, processed_part);
	free(temp_cleaned_lexeme);
	free(before_dollar);
	free(processed_part);
	return (result);
}

// char	*m_get_expand_string(char *lexeme, t_env *env_list)
// {
// 	char	*temp_cleaned_lexeme;
// 	char	*before_dollar;
// 	char	*processed_part;
// 	char	*result;
// 	char	*dollar_position;

// 	temp_cleaned_lexeme = m_clean_quotes(lexeme);
// 	dollar_position = ft_strchr(temp_cleaned_lexeme, '$');
// 	if (!dollar_position) // Sem $
// 		return (temp_cleaned_lexeme);
// 	before_dollar = m_extract_before_dollar(temp_cleaned_lexeme);
// 	processed_part = m_process_after_dollar(dollar_position, env_list);
// 	if (!before_dollar) // Garante que nunca seja nulo
// 		before_dollar = ft_strdup("");
// 	result = ft_strjoin(before_dollar, processed_part);
// 	free(temp_cleaned_lexeme);
// 	free(before_dollar);
// 	free(processed_part);
// 	return (result);
// }
