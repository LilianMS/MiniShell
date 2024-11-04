#ifndef PARSER_H
# define PARSER_H

// Libs
# include "minishell.h"
# include "tokenizer.h"

// Structs
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

#endif