#include "../includes/parser.h"

static char	*extract_quoted_segment(char *input, int *index)
{
	char	id_quote;
	int		start;
	int		end;

	id_quote = ft_is_quotes_type(input + *index, &start, &end);
	if (id_quote)
	{
		start += *index; // Ajusta o índice para o deslocamento atual
		end += *index;
		*index = end + 1; // Avança o índice para além do segmento
		return (ft_strndup(&input[start], end - start + 1));
	}
	return (NULL);
}

static char	*extract_plain_segment(char *input, int *index)
{
	int	start;

	start = *index;
	while (input[*index] && input[*index] != '\'' && input[*index] != '\"')
		(*index)++;
	if (*index > start)
		return (ft_strndup(&input[start], *index - start));
	return (NULL);
}

char	**split_by_quotes(char *input)
{
	char	*segment;
	char	**result;
	int		res_index;
	int		index;

	res_index = 0;
	index = 0;
	result = malloc(sizeof(char *) * (ft_strlen(input) + 1));
	if (!result)
		return (NULL);
	while (input[index])
	{
		// Primeiro, tenta extrair trechos sem aspas
		segment = extract_plain_segment(input, &index);
		if (!segment)
			segment = extract_quoted_segment(input, &index);
		result[res_index++] = segment;
	}
	result[res_index] = NULL;
	return (result);
}

// receber char ** 
// expandir array de variáveis de ambiente
// juntar tudo numa string e retornar

char	*m_get_expand_split(char **split, t_env *env_list)
{
	char	*expanded;
	char	*temp;
	int		i;

	expanded = ft_strdup("");
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '\'') && !ft_strchr(split[i], '\"')
			|| (ft_strchr(split[i], '\'') && ft_strchr(split[i], '\"') && split[i][0] == '\''))
			temp = m_clean_quotes(split[i]);
		else if ((split[i][0] == '$' && split[i][1] == '\0')
			|| split[i][2] == '\"' || split[i][2] == ' ')
			temp = m_expansion_special_cases(split[i]);
		else if (ft_strchr(split[i], '\"'))
			temp = m_get_expand_string(split[i], env_list);
		else
		{
			temp = m_get_expand_string(split[i], env_list);
			// printf("temp: %s\n", temp);
		}
		expanded = ft_strjoin_free(expanded, temp);
		i++;
	}
	free(split);
	return (expanded);
}