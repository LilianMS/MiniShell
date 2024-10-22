#ifndef TOKENIZER_H
# define TOKENIZER_H

//Libs
# include "minishell.h"

//Structs
typedef struct s_mini		t_mini;
typedef struct s_token		t_token;
typedef struct s_auto		t_auto;

//Structs
typedef struct s_token
{
	char	*lexeme;
	int		type;
	struct	s_token *next;
	struct	s_token *prev;
} t_token;

typedef struct s_auto
{
	int		i;
	int		lexeme_len;
	int		str_len;
	int		status;
	int		token_type;
	char	*lexeme;
} t_auto;

// Enums
enum e_token_type
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    UNKNOWN
};

t_token		*m_tokenize(t_token **tokens, char *input);
char		*m_get_lexeme(char *input, int start, int *i);

#endif