#ifndef AST_H
# define AST_H

// Libs
# include "minishell.h"
# include "parser.h"
# include "tokenizer.h"

// Structs
typedef struct s_tree	t_tree;
typedef struct s_token	t_token;

// Structs
struct s_tree
{
	char				*content;
	char				**command;
	int					type;
	int					index;
	struct t_tree		*left;
	struct t_tree		*right;
	struct t_tree		*parent;
};

// Functions
void	m_binary_tree(t_tree *root, t_token **parsed_list);
t_tree	*m_create_tree_node(t_tree *root, t_token *joint);
void	m_get_sublist(t_token *rev_list, t_token **parsed_list);
t_tree	*m_grow_tree(t_tree **root, t_token **joint, t_token *parsed_list);
t_tree	*m_tree_builder(t_token *parsed_list);

#endif