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

char	*m_quotes_and_expansion(char *lexeme, t_env *env_list)
{
	if (ft_strchr(lexeme, '$'))
	{
		if(ft_strchr(lexeme, '\'') || ft_strchr(lexeme, '\"'))
		{
			return (m_get_expand_split(lexeme, env_list));
		}
		else
			return (m_get_expand_string(ft_strdup(lexeme), env_list));
	}
	return (m_clean_quotes(ft_strdup(lexeme)));
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
