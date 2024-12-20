#include "../../includes/minishell.h"

// void	m_print_exit_status(int exit_status)
// {
// 	if (exit_status == 126)
// 		ft_putstr_fd("\033[31mError: Permission denied\033[37m\n", 2);
// 	else if (exit_status == 127)
// 		ft_putstr_fd("\033[31mError: Command not found\033[37m\n", 2);
// }

static char	**m_find_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (envp[i])
	{
		paths = ft_split(envp[i] + 5, ':');
		return (paths);
	}
	return (NULL);
}

char	*m_create_path(char *cmd_path, char **node_cmd, char **envp)
{
	char	*path;
	char	**env_paths;
	int		i;
	int		exit_status;

	i = 0;
	env_paths = m_find_paths(envp);
	while (env_paths[i])
	{
		path = ft_strjoin(env_paths[i++], "/");
		cmd_path = ft_strjoin(path, node_cmd[0]);
		free(path);
		exit_status = m_check_cmd(cmd_path); //está pegando o status de saída errado! >> arrumar
		if (exit_status == 0)
		{
			free_cmd_array(env_paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_cmd_array(env_paths); // --> reutilizando a função que dá free no array de comandos
	m_print_exit_status(exit_status);
	return (NULL);
}

char **m_env_list_to_array(t_env *env_list)
{
	t_env	*tmp;
	char	**envp;
	int		i;

	tmp = env_list;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_list)
	{
		envp[i] = ft_strjoin(env_list->name, "=");
		envp[i] = ft_strjoin(envp[i], env_list->value);
		env_list = env_list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	m_check_cmd(char *cmd_path)
{
	int	exit_status;

	exit_status = 0;
	if (access(cmd_path, F_OK) == -1)
		exit_status = 127;
	if (access(cmd_path, X_OK) == -1)
		exit_status = 126;
	return (exit_status);
}

int	m_execute_command(char **tree_node_cmd, t_env *env_list)
{
	char	*cmd_path;
	char	**env;
	int		exit_status;

	cmd_path = NULL;
	exit_status = 0;
	env = m_env_list_to_array(env_list);
	if (!env)
		return (1);
	cmd_path = m_create_path(cmd_path, tree_node_cmd, env);
	if (exit_status != 0)
		return (exit_status);
	if (execve(cmd_path, tree_node_cmd, env) == -1)
		exit_status = 1;
	return (exit_status);
}

int	m_execution(t_mini *mini, t_token **parsed_list)
{
	int		exit_status;

	exit_status = 0;
	if (!mini->tree)
		return (1); //checar esse código de retorno (erro na árvore = erro no parser)
	if (mini->tree->type == COMMAND)
	{
		if (m_is_builtin(mini->tree) != -1)
			exit_status = m_execute_builtin(mini, parsed_list);
		else
			exit_status = m_execute_command(mini->tree->command, mini->env_list);
	}
	// else
	// {
	// 	m_execution(tree->left);
	// 	m_execution(tree->right);
	// }
	if (exit_status != 0)
	{
		//TRANSFORMAR AS LINHAS ABAIXO EM UMA FUNÇÃO ÚNICA
		m_tree_cleaner(mini->tree);
		m_free_env_list(mini->env_list);
		m_free_tokens(parsed_list);
		// close_fds();
	}
	return (exit_status); //-> nao necessariamente precisa disso
}
