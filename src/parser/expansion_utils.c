#include "../includes/parser.h"

// função para expadir $$
pid_t	m_get_pid(void)
{
	return (8888);
}

char	*m_clean_dollar(char *str, int *idx)
{
	int		len;
	char	*var_name;

	len = 0;
	*idx = 0;
	// Avança para depois do $ e captura caracteres válidos para nome de variável
	while (str[len + 1] && (ft_isalnum(str[len + 1]) || str[len + 1] == '_'))
	{
		if (str[len + 1] == ' ' || str[len + 1] == '\"')
			break ;
		len++;
	}
	// while (str[len] == ' ')
	// 	len--; // Ignora espaço no final do nome da variável
	*idx = len + 1; // Atualiza o índice para a posição do caractere após o nome da variável
	ft_printf("idx: %d\n", *idx);
	var_name = ft_substr(str, 1, len); // Pula o $
	return (var_name);
}
