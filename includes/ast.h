#ifndef AST_H
# define AST_H

// Libs
# include "minishell.h"
# include "parser.h"
# include "tokenizer.h"

// Structs
typedef struct s_tree	t_tree;

// Structs
struct s_tree
{
	char				*content;
	char				**command;
	int					type;
	int					position;
	struct t_tree		*left;
	struct t_tree		*right;
	// struct t_tree		*parent;
};

// Functions

#endif