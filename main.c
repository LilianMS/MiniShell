#include <stdlib.h>
#include <stdio.h>

// Função equivalente a strlen
size_t ft_strlen(const char *s)
{
	size_t i = 0;
	while (s[i])
		i++;
	return i;
}

// Função equivalente a strcspn
size_t ft_strcspn(const char *s, const char *reject)
{
    size_t i = 0;
    while (s[i])
    {
        size_t j = 0;
        while (reject[j])
        {
            if (s[i] == reject[j])
                return i;
            j++;
        }
        i++;
    }
    return i;
}

// Função equivalente a strndup
char *ft_strndup(const char *s, size_t n)
{
    size_t i = 0;
    char *dup = malloc(n + 1); // +1 para o terminador nulo
    if (!dup)
        return NULL;
    while (i < n && s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0'; // Garantir que a string copiada seja terminada com '\0'
    return dup;
}

// Função fornecida
char ft_is_quotes_type(char *lexeme, int *start, int *end)
{
    char id_quote;
    int i;

    id_quote = 0;
    i = 0;
    while (lexeme[i])
    {
        if ((lexeme[i] == '\'' || lexeme[i] == '\"') && id_quote == 0)
        {
            id_quote = lexeme[i];
            *start = i;
        }
        else if (lexeme[i] == id_quote)
        {
            *end = i;
            return (id_quote);
        }
        i++;
    }
    *start = -1;
    *end = -1;
    return (0);
}

// Função para quebrar string com base em aspas
char **split_by_quotes(char *input)
{
    int start, end;
    char id_quote;
    char **result;
    int res_index = 0;
    int len = ft_strlen(input);

    result = malloc(sizeof(char *) * (len + 1)); // Alocar memória suficiente
    if (!result)
        return (NULL);

    while (*input)
    {
        // Identificar o trecho delimitado por aspas
        id_quote = ft_is_quotes_type(input, &start, &end);
        if (id_quote)
        {
            // Adicionar trecho com as aspas
            result[res_index++] = ft_strndup(input + start, end - start + 1);
            input += end + 1;
        }
        else
        {
            // Adicionar trecho sem aspas
            start = ft_strcspn(input, "\'\"");
            result[res_index++] = ft_strndup(input, start);
            input += start;
        }
    }
    result[res_index] = NULL; // Finalizar array de strings
    return (result);
}

int	m_qntd_dollar(char *str)
{
	int i = 0;
	int n = 0;

	while (str[i])
	{
		if (str[i] == '$')
			n++;
		i++;
	}
	return (n);
}


void identify_dollar_in_context(char **strings)
{
    int start, end;
    char quote_type;
    int i, j;

	i = 0;
	while (strings[i]) // Iterar sobre cada string
	{
		j = 0;
		while (strings[i][j])
		{
			quote_type = ft_is_quotes_type(&strings[i][j], &start, &end);
			if (quote_type == '\"') // Verifica aspas duplas
			{
				int k = start;
				while (k <= end)
				{
					if (strings[i][k] == '$')
						printf("Encontrado $ dentro de aspas duplas: %s\n", strings[i]);
					k++;
				}
				j = end + 1; // Salta para o final do trecho analisado
			}
			else if (quote_type == '\'') // Verifica aspas simples
			{
				// $ é ignorado dentro de aspas simples
				j = end + 1; // Salta para o final do trecho
			}
			else // Fora de aspas
			{
				if (strings[i][j] == '$')
					printf("Encontrado $ fora de aspas: %s\n", strings[i]);
				j++;
			}
		}
		i++;
	}
}



// Teste
int main(void)
{
    char *test = "\"$hello '$world' \"foo$bar\" test\"";
    char **result = split_by_quotes(test);
    int i = 0;

	identify_dollar_in_context(result);
    while (result[i])
    {
        printf("Segmento %d: %s\n", i, result[i]);
        free(result[i]);
        i++;
    }
    free(result);
    return (0);
}
