#include "../includes/builtin.h"
#include "../includes/debug.h" // --------- debug

// m_cd (not implemented)
// m_exit (in progress)
// m_env (ok)
// ft_echo (ok)
// ft_pwd (ok)
// m_unset (ok)
// m_export (ok)

int	m_is_builtin(t_token *parsed_list)
{
	// print_parsed_command(parsed_list); // --------- debug
	if (!parsed_list || !parsed_list->command)
		return (-1);
	if (ft_strcmp(parsed_list->command[0], "echo") == 0)
		return (ECHO);
	if (ft_strcmp(parsed_list->command[0], "cd") == 0)
		return (CD);
	if (ft_strcmp(parsed_list->command[0], "pwd") == 0)
		return (PWD);
	if (ft_strcmp(parsed_list->command[0], "env") == 0)
		return (ENV);
	if (ft_strcmp(parsed_list->command[0], "export") == 0)
		return (EXPORT);
	if (ft_strcmp(parsed_list->command[0], "unset") == 0)
		return (UNSET);
	if (ft_strcmp(parsed_list->command[0], "exit") == 0)
		return (EXIT);
	return (-1);
}

void	m_execute_builtin(t_mini *mini, t_token *parsed_list)
{
	char	**args;
	int		builtin;

	args = parsed_list->command;
	builtin = m_is_builtin(parsed_list);
	if (builtin == -1)
		return ;
	else
		print_parsed_command(parsed_list); // --------- debug
	if (builtin == PWD)
		ft_pwd();
	if (builtin == CD)
		ft_cd(args, mini->env_list);
	if (builtin == ECO)
		ft_echo(args);
	if (builtin == ENV)
		m_env(mini->env_list);
	if (builtin == EXPORT)
		m_export(mini->env_list, args);
	if (builtin == UNSET)
		m_unset(mini->env_list, args);
	if (builtin == EXIT)
		m_exit(&mini, &parsed_list);
}
