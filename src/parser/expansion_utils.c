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
	while (str[len + 1] && (ft_isalnum(str[len + 1]) || str[len + 1] == '_'))
	{
		if (str[len + 1] == ' ' || str[len + 1] == '\"')
			break ;
		len++;
	}
	*idx = len + 1;
	// ft_printf("idx: %d\n", *idx); // debug 
	var_name = ft_substr(str, 1, len);
	return (var_name);
}
