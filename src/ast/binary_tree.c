#include "../includes/ast.h"

//TO DO
// - IMPLEMENTAR FUNÇÃO QUE BUSCA O INDEX DO NÓ TARGET
// - IMPLEMENTAR FUNÇÃO QUE GERA UMA SUBLISTA A PARTIR DO INDEX ENCONTRADO + TAMANHO TOTAL DA LISTA
// - DAR UM JEITO DE MALLOCAR A NOVA LISTA COM A STRUCT T_TREE (*PARENT, *LEFT E *RIGHT)
// IMPLEMENTAR FUNÇÃO QUE PRINTA A ÁRVORE.

void	m_get_sublist(t_token *rev_list, t_token **parsed_list)
{
	int		list_len;
	int		i;
	t_token	*temp;

	i = 0;
	temp = rev_list;
	list_len = list_size(parsed_list);
	while (temp)
	{
		temp = temp->prev;
		i++;
	}
	ft_printf("index: %d / total len: %d\n\n", i, list_len);
	// while (i < list_len)
}

t_tree	*m_grow_tree(t_tree **root, t_token **rev_list, t_token **parsed_list)
{
	*root = m_create_tree_node(*root, *rev_list);
	// (*root)->right = m_get_sublist(*rev_list, parsed_list);
	m_get_sublist(*rev_list, parsed_list);
	// (*root)->left = m_get_sublist(*root, *rev_list);
	return (*root);
}

t_tree	*m_create_tree_node(t_tree *root, t_token *rev_list)
{
	root = ft_calloc(sizeof(t_tree), 1);
	if (!root)
		return (NULL);
	root->type = rev_list->type;
	root->index = 0;
	root->content = NULL;
	root->command = NULL;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	return (root);
}

void	m_binary_tree(t_tree *root, t_token **parsed_list)
{
	t_token *rev_list;

	rev_list = m_find_last_token(*parsed_list);
	while (rev_list && rev_list->type != PIPE)
		rev_list = rev_list->prev;
	
	root = m_grow_tree(&root, &rev_list, parsed_list);
	list_printer(&rev_list); // ----- debug
	ft_printf("Tree root: %s / Type: %d / Address: %p \n", root->content, root->type, root);
	free(root);
}