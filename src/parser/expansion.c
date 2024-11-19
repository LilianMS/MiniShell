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

static char	*m_process_after_dollar(char *dollar_position, t_env *env_list)
{
	char	*expansion;
	char	*remaining_text;
	char	*cleaned_lexeme;
	int		idx;

	remaining_text = NULL;
	if (m_is_special_cases_dollar(dollar_position))
	{
		expansion = m_expansion_special_cases(dollar_position);
		remaining_text = ft_strdup(dollar_position + 2);
	}
	else
	{
		cleaned_lexeme = m_clean_dollar(dollar_position, &idx);
		if (m_get_env(env_list, cleaned_lexeme))
			expansion = ft_strdup(m_get_env(env_list, cleaned_lexeme));
		else
			expansion = ft_strdup("");
		free(cleaned_lexeme);
		remaining_text = ft_strdup(dollar_position + idx);
	}
	if (!remaining_text) // Garante que nunca seja nulo
		remaining_text = ft_strdup("");
	return (ft_strjoin_free(expansion, remaining_text));
}

// char	*m_get_expand_string(char *lexeme, t_env *env_list)
// {
// 	char	*result;
// 	char	*dollar_position;
// 	char	*processed_part;
// 	char	*before_dollar;
// 	char	*temp;

// 	result = ft_strdup(""); // Inicializa como string vazia
// 	dollar_position = ft_strchr(lexeme, '$');

// 	while (dollar_position)
// 	{
// 		// Extrai a parte antes do $
// 		before_dollar = ft_substr(lexeme, 0, dollar_position - lexeme);
// 		temp = ft_strjoin(result, before_dollar);
// 		free(result);
// 		free(before_dollar);
// 		result = temp;

// 		// Processa o conteúdo após o $
// 		processed_part = m_process_after_dollar(dollar_position, env_list);
// 		temp = ft_strjoin_free(result, processed_part); // `ft_strjoin_free` usada aqui
// 		result = temp;

// 		// Atualiza o ponteiro para processar o restante do texto
// 		dollar_position = ft_strchr(dollar_position + 1, '$');
// 		lexeme = dollar_position ? dollar_position : ""; // Atualiza para texto restante
// 	}

// 	// Adiciona o restante do texto, se existir
// 	temp = ft_strjoin(result, lexeme);
// 	free(result);
// 	return (temp);
// }



// char	*m_get_expand_string(char *lexeme, t_env *env_list)
// {
// 	char	*temp_cleaned_lexeme;
// 	char	*result;
// 	char	*dollar_position;
// 	char	*processed_part;
// 	char	*before_dollar;

// 	result = ft_strdup(""); // Inicializa como string vazia
// 	temp_cleaned_lexeme = m_clean_quotes(lexeme);
// 	dollar_position = ft_strchr(temp_cleaned_lexeme, '$');
// 	while (dollar_position)
// 	{
// 		// Parte antes do $
// 		before_dollar = m_extract_before_dollar(temp_cleaned_lexeme);
// 		result = ft_strjoin_free(result, before_dollar);
// 		// Parte após o $
// 		processed_part = m_process_after_dollar(dollar_position, env_list);
// 		result = ft_strjoin_free(result, processed_part);
// 		// Avança no texto para o próximo $
// 		temp_cleaned_lexeme = dollar_position + 1;
// 		dollar_position = ft_strchr(temp_cleaned_lexeme, '$');
// 	}
// 	// Adiciona o restante do texto (sem $)
// 	result = ft_strjoin_free(result, ft_strdup(temp_cleaned_lexeme));
// 	return (result);
// }

char	*m_get_expand_string(char *lexeme, t_env *env_list)
{
	char	*temp_cleaned_lexeme;
	char	*before_dollar;
	char	*processed_part;
	char	*result;
	char	*dollar_position;

	temp_cleaned_lexeme = m_clean_quotes(lexeme);
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
