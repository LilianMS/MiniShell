/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:31 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/18 17:11:18 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/includes/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_mini			t_mini;
typedef struct s_token			t_token;

struct s_mini
{
	char	*input;
};

typedef struct s_token
{
	char	value;
	int		type;
	struct	s_token *next;
	struct	s_token *prev;
} t_token;

enum e_token_type
{
	WORD,
	OPERATOR,
};

enum e_token_final
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
};

// Lexical Analysis Functions
int		ft_check_quotes(const char *line);
void	m_lexical_analysis(char *line);
t_token	**m_tokenize(t_token **tokens, char *input);
void	print_tokens(t_token **tokens);
void	m_free_tokens(t_token **tokens);

// Parsing Functions

#endif