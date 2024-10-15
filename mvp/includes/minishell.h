/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:31 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/15 17:49:35 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../../libs/libft/includes/libft.h"
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_mini t_mini;

typedef enum e_token_type
{
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	VARIABLE,
	STRING,
	UNKNOWN
} t_token_type;

typedef struct s_token
{
	char *value;
	t_token_type type;
	struct s_token *next;   // Para formar uma lista encadeada de tokens
} t_token;

struct s_mini
{
	char	*input;
};

// Lexical Analysis Functions
int		m_check_quotes(const char *line);
void	m_lexical_analysis(char *line);


// Parsing Functions


// Debug Functions

void	print_tokens(t_token *tokens);

#endif