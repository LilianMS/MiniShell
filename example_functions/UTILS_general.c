#include "minishell.h"

// Função para verificar caracteres especiais
int	m_is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

// Função para pular espaços em branco
void	m_skip_whitespace(char *input, int *i)
{
	while (input[*i] && isspace(input[*i]))
		(*i)++;
}

// Função para processar operadores
void	m_operator_process(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		m_add_token(tokens, m_create_token("|", PIPE));
		(*i)++;
	}
	else if (input[*i] == '>') // exemplo para tratar >> -----------
	{
		if (input[*i + 1] == '>')
		{
			m_add_token(tokens, m_create_token(">>", REDIR_APPEND));
			(*i) += 2;
		}
		else
		{
			m_add_token(tokens, m_create_token(">", REDIR_OUT));
			(*i)++;
		}
	} // ---------------------------------------------------
	else if (input[*i] == '<')
	{
		m_add_token(tokens, m_create_token("<", REDIR_IN));
		(*i)++;
	}
}

// Função para tratar aspas em palavras
char	*m_handle_quotes(char *input, int *i)
{
	char quote;
	int start;

	quote = input[*i];
	start = ++(*i);  // Avança após a aspa
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)  // Fecha a aspa
		(*i)++;
	return ft_strndup(&input[start], (*i) - start - 1);  // Retorna o conteúdo entre aspas
}

// Função para tratar expansões de variáveis
char	*m_handle_expansion(char *input, int *i)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = ++(*i); // Avança após o '$'
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(&input[start], (*i) - start);
	var_value = getenv(var_name); // Obtém o valor da variável de ambiente
	free(var_name);
	if (var_value)
		return ft_strdup(var_value);
	else
		return ft_strdup(""); // Retorna string vazia se a variável não existir
}

// Função principal de tokenização
t_token	*m_tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	int		is_first;

	tokens = NULL;
	i = 0;
	is_first = 1;
	while (input[i])
	{
		m_skip_whitespace(input, &i);
		if (m_is_special_char(input[i]))
		{
			m_operator_process(input, &i, &tokens);
			is_first = 1; // Reinicia após operadores
		}
		else if (input[i])
		{
			m_word_process(input, &i, &tokens, is_first);
			is_first = 0;
		}
	}
	return tokens;
}