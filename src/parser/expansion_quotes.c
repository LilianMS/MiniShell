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

void print_char_array(char **array) // debug
{
    int i = 0;
    while (array[i])
    {
        ft_printf("String %d: %s\n", i, array[i]);
        i++;
    }
}

char **split_by_quotes(char *input)
{
    char    *segment;
    char    **result;
    int     res_index;
    int     index;

    res_index = 0;
    index = 0;
    result = malloc(sizeof(char *) * (ft_strlen(input) / 2 + 2)); // Melhor estimativa inicial
    if (!result)
        return (NULL);
    while (input[index])
    {
		if (input[index] == '\'' || input[index] == '\"')
            segment = extract_quoted_segment(input, &index);
		else
			segment = extract_plain_segment(input, &index);
        if (segment)
            result[res_index++] = segment;
    }
    result[res_index] = NULL;
	print_char_array(result); // debug
    return (result);
}

char	*m_get_expand_split(char *lexeme, t_env *env_list)
{
	char	*result;
	char	*new_expanded;
	char	*temp;
	char	**split;
	int		i;
	char	*dollar_position;

	split = split_by_quotes(lexeme);
	result = ft_strdup("");
	i = 0;
	while (split[i])
	{
		dollar_position = ft_strchr(split[i], '$');
		if (!dollar_position)
			new_expanded = m_clean_quotes(split[i]);
		else
		{
			dollar_position++;
			if ((ft_strchr(split[i], '\'') && !ft_strchr(split[i], '\"'))
				|| (ft_strchr(split[i], '\'') && ft_strchr(split[i], '\"') && split[i][0] == '\''))
				new_expanded = m_clean_quotes(split[i]);
			else if (ft_strchr(split[i], '\"') \
				&& (!ft_isalnum(*dollar_position) && *dollar_position != '_'
				&& *dollar_position != '?' && *dollar_position != '$'))
				new_expanded = m_clean_quotes(split[i]);
			// else if (ft_strchr(split[i], '\"'))
			// 	new_expanded = m_get_expand_string(split[i], env_list);
			else
				new_expanded = m_get_expand_string(split[i], env_list);
		}
		temp = ft_strjoin_free(result, new_expanded);
		result = temp;
		i++;
	}
	free(split);
	return (result);
}

// $HOME$$$?"$USER"'$eu'

// char	**split_by_quotes(char *input)
// {
// 	char	*segment;
// 	char	**result;
// 	int		res_index;
// 	int		index;

// 	res_index = 0;
// 	index = 0;
// 	result = malloc(sizeof(char *) * (ft_strlen(input) + 1));
// 	if (!result)
// 		return (NULL);
// 	while (input[index])
// 	{
// 		// Primeiro, tenta extrair trechos sem aspas
// 		segment = extract_plain_segment(input, &index);
// 		if (!segment)
// 			segment = extract_quoted_segment(input, &index);
// 		result[res_index++] = segment;
// 	}
// 	result[res_index] = NULL;
// 	return (result);
// }

// char *m_get_expand_split(char *lexeme, t_env *env_list)
// {
//     char    *expanded;
//     char    *temp;
//     char    **split;
//     int     i;

//     split = split_by_quotes(lexeme);
//     if (!split)
//         return (NULL);
//     expanded = ft_strdup("");
//     if (!expanded)
//         return (NULL); // ft_strdup deve lidar com falhas
//     i = 0;
//     while (split[i])
//     {
//         if ((ft_strchr(split[i], '\'') && !ft_strchr(split[i], '\"'))
//             || (ft_strchr(split[i], '\'') && ft_strchr(split[i], '\"') && split[i][0] == '\''))
//             temp = m_clean_quotes(split[i]);
//         else if ((split[i][0] == '$' && split[i][1] == '\0')
//                 || split[i][2] == '\"' || split[i][2] == ' ')
//             temp = m_clean_quotes(split[i]);
//         else
//             temp = m_get_expand_string(split[i], env_list);

//         // if (!temp) // Falha ao expandir
//         // {
//         //     free(expanded);
//         //     while (split[i])
//         //         free(split[i++]);
//         //     free(split);
//         //     return (NULL);
//         // }
//         expanded = ft_strjoin_free(expanded, temp);
//         // free(temp);
//         i++;
//     }
//     // i = 0;
//     // while (split[i])
//     //     free(split[i++]); // Libera cada string individual
//     free(split); // Libera o array
//     return (expanded);
// }
