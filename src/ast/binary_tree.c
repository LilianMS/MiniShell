#include "ast.h"

t_tree	*m_grow_tree(t_tree *root, t_token **joint, t_token *parsed_list)
{
	t_token	*right;
	t_token	*left;

	right = NULL;
	left = parsed_list;
	if(!root || !*joint || !parsed_list)
		return (NULL);
	right = (*joint)->next;
	if(right)
		right->prev = NULL;
	root->type = (*joint)->type;
	left = (*joint)->prev;
	if (left)
		left->next = NULL;
	root->left = m_tree_builder(left);
	root->right = m_tree_builder(right);
	return (root);
}

t_tree	*m_create_tree_node(t_tree *root, t_token *joint)
{
	root = ft_calloc(sizeof(t_tree), 1);
	// if (!root)
	// 	return (NULL);
	// root->type = joint->type;
	// root->index = 0;
	// root->content = NULL;
	// root->command = NULL;
	// root->left = NULL;
	// root->right = NULL;
	// root->parent = NULL;
	return (root);
}

int	m_is_redir(int	token_type)
{
	return (token_type == REDIR_APPEND \
		|| token_type == REDIR_HEREDOC \
		|| token_type == REDIR_OUT \
		|| token_type == REDIR_IN);
}

t_token	*m_find_joint_token(t_token	*tokens)
{
	t_token *rev_list;

	rev_list = m_find_last_token(tokens);
	while (rev_list && rev_list->type != PIPE)
			rev_list = rev_list->prev;
	if (rev_list && rev_list->type == PIPE)
			return (rev_list);
	rev_list = m_find_last_token(tokens);
	while (rev_list && !m_is_redir(rev_list->type))
		rev_list = rev_list->prev;
	if (rev_list && m_is_redir(rev_list->type))
		return (rev_list);
	return (NULL);
}

t_tree	*m_tree_builder(t_token *parsed_list)
{
	t_token	*joint;
	t_tree	*root;

	joint = m_find_joint_token(parsed_list);
	// ft_printf("First joint: %s / Type: %d / Address: %p \n", joint->lexeme, joint->type, joint); // ---debug
	root = ft_calloc(sizeof(t_tree), 1);
	root->left = NULL;
	root->right = NULL;
	m_grow_tree(root, &joint, parsed_list);
	// list_printer(&joint); // ----- debug
	ft_printf("Tree root: %s / Type: %d / Address: %p \n", root->content, root->type, root); // ----- debug
	return (root);

}

void	m_binary_tree(t_tree *root, t_token **parsed_list)
{
	t_tree	*tmp;

	root = m_tree_builder(*parsed_list);
	// visualize_tree(root);
	//função p/ limpar a árvore.
}