#include "../includes/parser.h"

// função para expadir $$
pid_t	m_get_pid(void)
{
	return (8888);
}

// função para setar e pegar o status do sinal ao chamar $?
char	*m_set_get_status(int code_exit)
{
	char *temp;

	temp = ft_itoa(g_signal_status);
	g_signal_status = code_exit;
	temp = ft_strjoin_free(temp, ": command not found");
	return (temp);
}

char	*m_clean_dollar(char *str, int *idx)
{
	int		len;
	char	*var_name;

	len = 0;
	*idx = 0;
	while (str[len + 1] && (ft_isalnum(str[len + 1]) || str[len + 1] == '_'))
	{
		if (str[len + 1] == ' ' || str[len + 1] == '\"' || str[len + 1] == '$')
			break ;
		len++;
	}
	*idx = len + 1;
	// ft_printf("idx: %d\n", *idx); // debug 
	var_name = ft_substr(str, 1, len);
	return (var_name);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (result);
}
