#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//teste
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && len < size - 1)
		{
			dst[i] = src[i];
			i++;
			len++;
		}
		dst[i] = '\0';
		return (ft_strlen(src));
	}
	else
		return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*dst;

	dst = malloc(ft_strlen (s) + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s, ft_strlen (s) + 1);
	return (dst);
}

char	*m_clean_quotes(char *lexeme)
{
	char	*new_lexeme;
	int		i;
	int		str_len;

	i = 0;
	str_len = ft_strlen(lexeme);
	if (((lexeme[0] == '\"') && (lexeme[str_len - 1] == '\"'))
		|| ((lexeme[0] == '\'') && (lexeme[str_len - 1] == '\'')))
	{
		str_len -= 2;
		new_lexeme = malloc(sizeof(char) * (str_len + 1));
		while (lexeme[i + 1])
		{
			new_lexeme[i] = lexeme[i + 1];
			i++;
		}
		new_lexeme[i - 1] = '\0';
		free(lexeme);
		return (new_lexeme);
	}
	return (lexeme);
}

int main()
{
    char *str = ft_strdup("\"teste\"");
    printf("str =>> %s\n", str);
    str = m_clean_quotes(str);
    printf("str =>> %s\n", str);
	free(str);
    return (0);
}
