#ifndef EXECUTION_H
#define EXECUTION_H

// Libs
#include "minishell.h"
#include "parser.h"
#include "tokenizer.h"
#include "debug.h"
#include "ast.h"

//Structs
typedef struct s_mini		t_mini;
typedef struct s_token		t_token;

//Functions
void	m_execution(t_mini *mini, t_token **parsed_list);

#endif