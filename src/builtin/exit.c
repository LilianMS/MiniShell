#include "../includes/builtin.h"

int	ft_is_valid_arg(const char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	if (*str == '\0')
		return (0);
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		num = num * 10 + (*str - '0');
		str++;
	}
	num *= sign;
	if (num < INT_MIN || num > INT_MAX)
		return (0);
	return (1);
}

int	m_exit(t_mini **mini, char **args)
{
	int	args_len;

	args_len = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	while (args[args_len])
		args_len++;
	if (args_len > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (args_len == 2)
	{
		if (ft_is_valid_arg(args[1]))
			(*mini)->exit_status = ft_atoi(args[1]) % 256;
		else
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			(*mini)->exit_status = 2;
		}
	}
	if ((*mini)->hdoc->filename)
		m_heredoc_delete_files(*mini);
	m_free_everything(*mini);
	exit((*mini)->exit_status);
}
