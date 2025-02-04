#include "../includes/ast.h"

void	m_tree_cleaner(t_tree *tree_node)
{
	if (tree_node)
	{
		m_tree_cleaner(tree_node->left);
		m_tree_cleaner(tree_node->right);
		if (tree_node->content)
			free(tree_node->content);
		if (tree_node->command)
			free_cmd_array(tree_node->command);
		free(tree_node);
		tree_node = NULL;
	}
}

void	m_add_parent(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
	{
		root->left->parent = root;
		m_add_parent(root->left);
	}
	if (root->right)
	{
		root->right->parent = root;
		m_add_parent(root->right);
	}
}