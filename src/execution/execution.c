#include "../../includes/minishell.h"

void	m_free_everything(t_mini *mini, t_token **parsed_list)
{
	m_free_env_list(mini->env_list);
	m_free_tokens(parsed_list);
	m_tree_cleaner(mini->tree);
}

int m_check_cmd(char *cmd_path)
{
	int exit_status;

	exit_status = 0;
	if (access(cmd_path, F_OK) == -1)
		exit_status = 127;
	else if (access(cmd_path, F_OK | X_OK) == -1)
		exit_status = 126;
	return (exit_status);
}

int m_execute_command(char **tree_node_cmd, t_env *env_list)
{
	char *cmd_path;
	char **env;

	cmd_path = NULL;
	env = m_env_list_to_array(env_list);
	if (!env)
		return (1);
	cmd_path = m_create_path(cmd_path, tree_node_cmd, env);
	if (cmd_path == NULL)
	{
		free(cmd_path);
		free_cmd_array(env);
		return (127);
	}
	execve(cmd_path, tree_node_cmd, env);
	free(cmd_path);
	free_cmd_array(env);
	return (1);
}

int	m_simple_command(t_mini *mini, t_token **parsed_list)
{
	int pid;

	pid = 0;
	if (mini->tree->type == COMMAND)
	{
		if (m_is_builtin(mini->tree) != -1)
			mini->exit_status = m_execute_builtin(mini, parsed_list);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				mini->exit_status = m_execute_command(mini->tree->command, mini->env_list);
				m_free_everything(mini, parsed_list);
				exit(mini->exit_status);
			}
			else
			{
				waitpid(pid, &mini->exit_status, 0);
				mini->exit_status = WEXITSTATUS(mini->exit_status);
			}
		}
	}
	return (mini->exit_status);
}

t_tree *m_find_leftmost_pipe(t_tree *node)
{
	t_tree *current;

	current = node;
	while (current && current->left && current->type == PIPE)
		current = current->left;
	if (current->type != PIPE)
		current = current->parent;
	ft_putendl_fd(current->content, STDERR_FILENO);			//	-->debug
	ft_putstr_fd(current->left->command[0], STDERR_FILENO); //	-->debug
	ft_putendl_fd("", STDERR_FILENO);						//				-->debug
	return (current);
}

int	m_exec_pipe_command(t_mini *mini, t_token **parsed_list, t_tree *original_root)
{
	int status;

	status = 0;
	if (mini->tree->type == COMMAND)
	{
		if (m_is_builtin(mini->tree) != -1)
			status = m_execute_builtin(mini, parsed_list);
		else
			status = m_execute_command(mini->tree->command, mini->env_list);
	}
	mini->tree = original_root;
	m_free_everything(mini, parsed_list);
	return (status);
}

int	m_execute_pipe(t_mini *mini, t_redir *redir_fd, t_token **parsed_list, t_tree *cmd_node)
{
	pid_t pid;
	t_tree *original_root;

	original_root = mini->tree;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
	{
		mini->tree = cmd_node;
		if (m_is_redir(mini->tree->type))
			m_execute_all_redirs(redir_fd, mini->tree);
		if (mini->tree->type == COMMAND)
			exit(mini->exit_status = m_exec_pipe_command(mini, parsed_list, original_root));
		mini->tree = original_root;
		m_free_everything(mini, parsed_list);
		exit(1);
	}
	return (pid);
}

// FUNÇÃO QUE LIDA COM PIPE DEVE ABRIR PIPE(PIPEFD) PARA CADA PIPE QUE FOR ENCONTRADO NA LINHA DE COMANDO
// DEVE FECHAR O PIPE(PIPEFD) APÓS A EXECUÇÃO DO COMANDO (???????)
// NO PROCESSO FILHO A BUILTIN PRECISA EXECUTAR COM FORK TAMBÉM - OU SEJA, A M_SIMPLE_COMMAND NÃO SERVE NESSE CASO.

int m_handle_pipe(t_mini *mini, t_redir *redir_fd, t_token **parsed_list)
{
	int pipe_fd[2];
	pid_t pid;
	t_tree *current;
	t_tree *cmd_node;

	m_init_redirect(redir_fd);
	current = m_find_leftmost_pipe(mini->tree);
	while (current && current->type == PIPE)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("minishell: pipe");
			return (1);
		}
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		cmd_node = current->left;
		if (cmd_node->type != COMMAND)
			cmd_node = current->parent->right;
		m_execute_pipe(mini, redir_fd, parsed_list, cmd_node);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		if (current->parent)
			current = current->parent;
		else
			break;
	}
	pid = m_execute_pipe(mini, redir_fd, parsed_list, current->right);
	m_restore_redirect(redir_fd);
	while (wait(&mini->exit_status) > 0)
		;
	if (WIFEXITED(mini->exit_status))
		return (WEXITSTATUS(mini->exit_status));
	return (1);
}

void m_execution(t_mini *mini, t_token **parsed_list)
{
	t_redir redir_fd;

	ft_bzero(&redir_fd, sizeof(t_redir));
	if (!mini->tree)
		mini->exit_status = 1;
	if (mini->tree->type == COMMAND)
		mini->exit_status = m_simple_command(mini, parsed_list);
	else if (m_is_redir(mini->tree->type))
		mini->exit_status = m_handle_redir(mini, &redir_fd, parsed_list);
	else if (mini->tree->type == PIPE)
		mini->exit_status = m_handle_pipe(mini, &redir_fd, parsed_list);
	if (mini->tree->content)
		ft_putendl_fd(mini->tree->content, STDERR_FILENO); //	-->debug
	m_tree_cleaner(mini->tree);
	m_free_tokens(parsed_list);
}


