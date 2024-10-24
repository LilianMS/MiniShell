#ifndef TOKENIZER_H
# define TOKENIZER_H

//Libs
# include "minishell.h"

//Structs
typedef struct s_mini		t_mini;
typedef struct s_token		t_token;
typedef struct s_automat	t_automat;

//Structs
typedef struct s_token
{
	char	*lexeme;
	int		type;
	struct	s_token *next;
	struct	s_token *prev;
} t_token;

typedef struct s_automat
{
	int		i;
	int		lexeme_len;
	int		str_len;
	int		status;
	int		token_type;
	char	*lexeme;
} t_automat;

// Enums
enum e_token_type
{
    WORD,
	OPERATOR, //temporário para testar funcionamento do tokenizer
    PIPE,
    REDIR_IN,
	REDIR_HEREDOC,
    REDIR_OUT,
    REDIR_APPEND,
    UNKNOWN
};

//Tokenizer core functions
void		m_tokenize(t_token **token_list, char *input);
void		m_get_token_list(t_automat *aut, t_token **token, char *input);

//Automaton functions
int			m_is_special_char(char c);
void		m_skip_whitespace(char *input, int *i);


//Token List functions
t_token		*m_create_token(char *lexeme, int type);
t_token		*m_find_last_token(t_token *token_ptr);
t_token		*m_add_token(t_token **token_list, t_token *new_token);
void		m_free_tokens(t_token **tokens);

#endif