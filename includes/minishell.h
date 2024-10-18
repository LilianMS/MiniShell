

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
	char	*value;
	int		type;
	struct s_token *next; // Para formar uma lista encadeada de tokens
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
int		m_check_quotes(const char *line);
void	m_lexical_analysis(char *line);

// Parsing Functions

#endif