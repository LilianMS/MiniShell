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

t_tree	*m_grow_tree(t_tree **root, t_token **joint)
{
	*root = m_create_tree_node(*root, *joint);
	// (*root)->right = m_get_sublist(*rev_list, parsed_list);
	// m_get_sublist(*rev_list, parsed_list);
	// (*root)->left = m_get_sublist(*root, *rev_list);
	return (*root);
}

t_tree	*m_create_tree_node(t_tree *root, t_token *joint)
{
	root = ft_calloc(sizeof(t_tree), 1);
	if (!root)
		return (NULL);
	root->type = joint->type;
	root->index = 0;
	root->content = NULL;
	root->command = NULL;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
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

void	m_binary_tree(t_tree *root, t_token **parsed_list)
{
	t_token	*joint;

	joint = m_find_joint_token(*parsed_list);
	if (joint)
	{
		ft_printf("First joint: %s / Type: %d / Address: %p \n", joint->lexeme, joint->type, joint); // ---debug
		root = m_grow_tree(&root, &joint);
		list_printer(&joint); // ----- debug
		ft_printf("Tree root: %s / Type: %d / Address: %p \n", root->content, root->type, root);
		free(root);
	}
}