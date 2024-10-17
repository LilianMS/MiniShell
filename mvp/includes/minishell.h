/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:31 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/17 12:19:10 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libs/libft/includes/libft.h"
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_mini	t_mini;

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
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next; // Para formar uma lista encadeada de tokens
}	t_token;

struct s_mini
{
	char	*input;
};

// Lexical Analysis Functions
int		m_check_quotes(const char *line);
void	m_lexical_analysis(char *line);

// Token Functions

// t_token	*m_tokenize(char *input);

// t_token	*m_create_token(char *value, t_token_type type);
// void	m_free_tokens(t_token *tokens);
// void	m_add_token(t_token **token_list, t_token *new_token);
// int		m_is_special_char(char c);

// void	m_skip_whitespace(char *input, int *i);
// void	m_process_operator(char *input, int *i, t_token **tokens);
// void	m_process_word(char *input, int *i, t_token **tokens);

// Parsing Functions

// ---- Debug Functions

void	print_tokens(t_token *tokens);

#endif