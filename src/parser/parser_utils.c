#include "../includes/parser.h"

// --- funções para m_quotes_and_expansion
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
	int	i;
	int	n;

	i = 0;
	n = 0;
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
	char	*dollar_position;

	dollar_position = ft_strchr(lexeme, '$');

	// id_quote = ft_is_qt_type(lexeme);
	// n_dollar = m_qntd_dollar(lexeme);
	// if (ft_strchr(lexeme, '$') && (id_quote == '\"' || id_quote == 0))
	// {
	// 	if (n_dollar > 1 && !(m_is_special_cases_dollar(lexeme)))
	// 		return (1);
	// 	else if ((lexeme[0] == '$' && lexeme[1] == '\0')
	// 		|| lexeme[2] == '\"' || lexeme[2] == ' ')
	// 		return (0);
	// 	return (1);
	// }
	return (0);
}

// char	*m_quotes_and_expansion(char *lexeme, t_env *env_list)
// {
// 	char	id_quote;

// 	id_quote = ft_is_qt_type(lexeme);
// 	if (!id_quote) // Sem aspas, verifica expansão
// 		return (m_get_expand_string(lexeme, env_list));
// 	else if (id_quote == '\'') // Aspas simples, apenas limpa
// 		return (m_clean_quotes(lexeme));
// 	else if (id_quote == '\"') // Aspas duplas, permite expansão
// 	{
// 		char	*cleaned = m_clean_quotes(ft_strdup(lexeme)); // Remove as aspas
// 		char	*expanded = m_get_expand_string(cleaned, env_list);
// 		free(cleaned);
// 		return (expanded);
// 	}
// 	return (ft_strdup(lexeme)); // Retorna original se nada se aplicar
// }

void print_char_array(char **array)
{
    int i = 0;
    while (array[i])
    {
        printf("String %d: %s\n", i, array[i]);
        i++;
    }
}

char *ft_test_temp(char *lexeme, t_env *env_list) // debug
{
	char **split = split_by_quotes(lexeme);
	print_char_array(split);
	char *result = m_get_expand_split(split, env_list);
	return (result);
}


char	*m_quotes_and_expansion(char *lexeme, t_env *env_list)
{
	// int	is_expand;

	// is_expand = m_check_expand(lexeme);
	// if (is_expand)
	// {
	// 	return (m_get_expand_string(lexeme, env_list));
	// }

	if (ft_strchr(lexeme, '$'))
	{
		if(ft_strchr(lexeme, '\'') || ft_strchr(lexeme, '\"'))
		{
			return (ft_test_temp(lexeme, env_list));
		}
		else
			return (m_get_expand_string(lexeme, env_list));
	}
	return (m_clean_quotes(lexeme));
}

t_token	*m_create_cmd_token(t_token *start, int command_len, t_env *env_list)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	ft_bzero(token, sizeof(t_token));
	if (!token)
		return (NULL);
	token->command = m_populate_cmd_array(start, command_len, env_list);
	token->command_len = command_len; // teste ---- debug ?
	token->type = COMMAND;
	token->position = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
