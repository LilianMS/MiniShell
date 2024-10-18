#include "minishell.h"

char	*ft_rrealloc(char *ptr, size_t new_size)
{
	char	*new_ptr;

	new_ptr =(char *)realloc(ptr, new_size); // modificar função
	if (!new_ptr)
	{
		free(ptr);
		return NULL;
	}
	return (new_ptr);
}


char	*append_substring(char *word, char *input, int start, int end)
{
	char	*substring;

	substring = ft_strndup(&input[start], end - start);
	if (!substring) 
		return NULL;
	word = ft_rrealloc(word, ft_strlen(word) + ft_strlen(substring) + 1);
	if (!word) 
	{
		free(substring);
		return NULL;
	}
	ft_strcat(word, substring);
	free(substring);
	return (word);
}

char	*process_expansion(char *input, int *i, char *word, int start)
{
	char	*expanded_word;

	if (*i > start)
		word = append_substring(word, input, start, *i);
	expanded_word = m_handle_expansion(input, i);
	word = ft_rrealloc(word, ft_strlen(word) + ft_strlen(expanded_word) + 1);
	if (!word) 
		return NULL;
	ft_strcat(word, expanded_word);
	free(expanded_word);
	return word;
}

char	*process_quotes(char *input, int *i, char *word, int start)
{
	char	*quoted_word;

	if (*i > start)
		word = append_substring(word, input, start, *i);
	quoted_word = m_handle_quotes(input, i);
	word = ft_rrealloc(word, ft_strlen(word) + ft_strlen(quoted_word) + 1);
	if (!word) 
		return NULL;
	ft_strcat(word, quoted_word);
	free(quoted_word);
	return (word);
}

char	*process_remaining_word(char *input, int *i, char *word, int start)
{
	if (start < *i) {
		word = append_substring(word, input, start, *i);
	}
	return (word);
}

void	m_word_process(char *input, int *i, t_token **tokens, int is_first)
{
	char			*word; 
	int				start;
	t_token_type	type;

	word = ft_strdup(""); 
	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !m_is_special_char(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			word = process_quotes(input, i, word, start);
		else if (input[*i] == '$')
			word = process_expansion(input, i, word, start);
		else
			(*i)++;
	}
	word = process_remaining_word(input, i, word, start);
	if (is_first)
		type = CMD;
	else
		type = ARG;
	m_add_token(tokens, m_create_token(word, type));
	free(word);
}
