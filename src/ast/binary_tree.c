#include "../includes/ast.h"

t_tree	*m_create_tree_node(t_tree *root, t_token *rev_list)
{
	root = ft_calloc(sizeof(t_tree), 1);
	if (!root)
		return (NULL);
	root->type = rev_list->type;
	root->content = NULL;
	root->command = NULL;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

void	m_binary_tree(t_tree *root, t_token **parsed_list)
{
	t_token *rev_list;

	rev_list = m_find_last_token(*parsed_list);
	while (rev_list && rev_list->type != PIPE)
		rev_list = rev_list->prev;
	root = m_create_tree_node(root, rev_list);
	list_printer(&rev_list); // ----- debug
	ft_printf("Tree root: %s (Type: %d)\n", root->content, root->type);
	free(root);
}