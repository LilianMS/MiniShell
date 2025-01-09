#include "../../includes/minishell.h"

static int	m_execute_redir_in(t_tree *current, t_redir *redir_fd)
{
	if (current->type == REDIR_IN)
		redir_fd->current_fd = open(current->right->content, O_RDONLY);
	if (redir_fd->current_fd == -1)
	{
		perror("minishell: input redirection");
		m_restore_redirect(redir_fd);
		return (1);
	}
	if (dup2(redir_fd->current_fd, STDIN_FILENO) == -1)
	{
		ft_putnbr_fd(redir_fd->current_fd, STDERR_FILENO);	   // -->debug
		ft_putendl_fd(current->right->content, STDERR_FILENO); // -->debug
		perror("minishell: dup2 error");
		close(redir_fd->current_fd);
		m_restore_redirect(redir_fd);
		return (1);
	}
	close(redir_fd->current_fd);
	return (0);
}

static int	m_execute_redir_out_append(t_tree *current, t_redir *redir_fd)
{
	if (current->type == REDIR_OUT)
	{
		redir_fd->current_fd = open(current->right->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_putendl_fd(current->right->content, STDERR_FILENO); // -->debug
	}
	else if (current->type == REDIR_APPEND)
		redir_fd->current_fd = open(current->right->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir_fd->current_fd == -1)
	{
		perror("minishell: output redirection");
		m_restore_redirect(redir_fd);
		return (1);
	}
	if (dup2(redir_fd->current_fd, STDOUT_FILENO) == -1)
	{
		ft_putnbr_fd(redir_fd->current_fd, STDERR_FILENO); // -->debug
		ft_putendl_fd(" OUT", STDERR_FILENO);			   // -->debug
		perror("minishell: dup2 error");
		close(redir_fd->current_fd);
		m_restore_redirect(redir_fd);
		return (1);
	}
	close(redir_fd->current_fd);
	return (0);
}

t_tree	*m_find_command_node(t_tree *node)
{
	t_tree	*current;

	current = node;
	if (current->left)
	{
		while (current->left && current->type != COMMAND)
			current = current->left;
	}
	return (current);
}

static int	m_execute_all_redirs(t_redir *redir_fd, t_tree *node)
{
	t_tree	*current;

	m_init_redirect(redir_fd);
	current = m_find_command_node(node);
	if (current->type == COMMAND)
		current = current->parent;
	while (current && m_is_redir(current->type))
	{
		// ALTERAR HEREDOC PARA ACEITAR T_TREE AO INVÉS DE T_TOKEN
		//  if (mini->tree->type == REDIR_HEREDOC)
		//  	m_heredoc(parsed_list);
		if (current->type == REDIR_IN)
			m_execute_redir_in(current, redir_fd);
		else if (current->type == REDIR_OUT)
			m_execute_redir_out_append(current, redir_fd);
		else if (current->type == REDIR_APPEND)
			m_execute_redir_out_append(current, redir_fd);
		current = current->parent;
	}
	return (0);
}

int	m_handle_redir(t_mini *mini, t_redir *redir_fd, t_token **parsed_list)
{
	t_tree	*original_root;
	t_tree	*cmd_node;
	int		status;

	status = 0;
	original_root = mini->tree;
	if (m_execute_all_redirs(redir_fd, mini->tree))
		return (1);
	cmd_node = m_find_command_node(mini->tree);
	if (!cmd_node)
	{
		m_restore_redirect(redir_fd);
		return (1);
	}
	mini->tree = cmd_node;
	status = m_simple_command(mini, parsed_list);
	m_restore_redirect(redir_fd);
	mini->tree = original_root;
	return (status);
}