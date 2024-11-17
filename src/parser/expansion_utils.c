#include "../includes/parser.h"

// função para expadir $$
pid_t	m_get_pid(void)
{
	return (8888);
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

char	*m_clean_dollar(char *str)
{
	char	*new_str;
	int		i;
	int		n;

	n = m_qntd_dollar(str);
	i = 0;
	new_str = malloc(sizeof(char) * ((ft_strlen(str) - n) + 1));
	while (str[i])
	{
		if (str[i] == '$')
			i++;
		*new_str++ = str[i];
		i++;
	}
	*new_str = '\0';
	new_str -= (ft_strlen(str) - 1);
	return (new_str);
}
