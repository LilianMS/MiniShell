#include "../includes/builtin.h"

static void	cd_print_error(char *folder)
{
	int			length;
	char		*message_to_print;
	const char	*message[2] = {"ERROR: cd: '", \
								"': file or directory does not exist"};

	length = ft_strlen(message[0]) + ft_strlen(folder) \
						+ ft_strlen(message[1]) + 1;
	message_to_print = malloc(length);
	ft_strlcpy(message_to_print, message[0], length);
	ft_strlcat(message_to_print, folder, length);
	ft_strlcat(message_to_print, message[1], length);
	ft_putendl_fd(message_to_print, 2);
	free(message_to_print);
}

static int	cd_aux(char **args, t_mini *mini, char **path)
{
	*path = NULL;
	if (args[1] && args[2])
	{
		ft_putendl_fd("ERROR: cd: Too many arguments", 2);
		return (1);
	}
	if (args[1] == NULL)
		*path = m_get_env(mini->env_list, "HOME");
	else
		*path = ft_strdup(args[1]);
	if (!*path[0])
	{
		ft_putendl_fd("ERROR: cd: HOME not defined", 2);
		free(*path);
		return (1);
	}
	return (0);
}

int		ft_cd(char **args, t_mini *mini)
{
    char	*path;
	char	*oldpwd;

	if (cd_aux(args, mini, &path) == 1)
	{
		free(path);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		oldpwd = m_get_env(mini->env_list, "PWD");
	if (chdir(path) == -1)
	{
		cd_print_error(path);
		free(path);
		free(oldpwd);
		return (1);
	}
	free(path);
    exp_update_or_add_env(&mini->env_list, "OLDPWD", oldpwd);
	free(oldpwd);
	path = getcwd(NULL, 0);
    exp_update_or_add_env(&mini->env_list, "PWD", path);
	free(path);
	return (0);
}
