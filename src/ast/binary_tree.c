#include "../includes/ast.h"

t_token	*m_find_joint_token(t_token	*tokens)
{
	t_token	*rev_list;

	if (!tokens)
		return (NULL);
	rev_list = m_find_last_token(tokens);
	while (rev_list && rev_list->type != PIPE)
		rev_list = rev_list->prev;
	if (rev_list && rev_list->type == PIPE)
	{
		rev_list->lexeme = ft_strdup("(pipe)");
		return (rev_list);
	}
	rev_list = m_find_last_token(tokens);
	while (rev_list && !m_is_redir(rev_list->type))
		rev_list = rev_list->prev;
	if (rev_list && m_is_redir(rev_list->type))
	{
		rev_list->lexeme = ft_strdup("(redir)");
		return (rev_list);
	}
	return (NULL);
}

void	m_allocate_command(t_tree **root, t_token *parsed_list)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (parsed_list->command[len])
		len++;
	(*root)->command_len = len;
	(*root)->type = parsed_list->type;
	(*root)->command = malloc(sizeof(char *) * (len + 1));
	while (len)
	{
		(*root)->command[i] = ft_strdup(parsed_list->command[i]);
		i++;
		len--;
	}
	(*root)->command[i] = NULL;
}

void	m_grow_tree(t_tree *root, t_token **joint)
{
	t_token	*right;
	t_token	*left;

	right = NULL;
	left = NULL;
	if (!root || !*joint)
		return ;
	right = (*joint)->next;
	if (right)
		right->prev = NULL;
	if ((*joint)->prev)
		left = (*joint)->prev;
	if (left)
		left->next = NULL;
	root->type = (*joint)->type;
	if ((*joint)->lexeme)
		root->content = ft_strdup((*joint)->lexeme);
	root->right = m_tree_builder(right);
	root->left = m_tree_builder(left);
}

t_tree	*m_tree_builder(t_token *parsed_list)
{
	t_token	*joint;
	t_tree	*root;

	if (!parsed_list)
		return (NULL);
	joint = m_find_joint_token(parsed_list);
	root = ft_calloc(sizeof(t_tree), 1);
	root->left = NULL;
	root->right = NULL;
	if (!joint && parsed_list->type == COMMAND)
		m_allocate_command(&root, parsed_list);
	if (!joint && (parsed_list->type == FILENAME \
		|| parsed_list->type == DELIMITER))
	{
		root->content = ft_strdup(parsed_list->lexeme);
		root->type = parsed_list->type;
	}
	m_grow_tree(root, &joint);
	if (joint && joint->prev)
	{
		m_free_tokens(&joint);
		joint = NULL;
	}
	return (root);
}

t_tree	*m_binary_tree(t_tree *root, t_token **parsed_list)
{
	root = m_tree_builder(*parsed_list);
	m_add_parent(root);
	m_free_tokens(parsed_list);
	return (root);
}
