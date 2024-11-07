#ifndef TOKENIZER_H
# define TOKENIZER_H

//Libs
# include "minishell.h"
# include "parser.h"

//Structs
typedef struct s_mini		t_mini;
typedef struct s_token		t_token;
typedef struct s_automat	t_automat;

//Structs
typedef struct s_token
{
	char			*lexeme;
	char			**command;
	int				type;
	int				command_len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_automat
{
	char	*lexeme;
	int		i;
	int		lexeme_len;
	int		str_len;
	int		status;
	int		token_type;
}	t_automat;

// Enums
enum e_token_type
{
	UNKNOWN = -1,
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND,
	COMMAND,
};

//Tokenizer core functions
t_token	**m_tokenize(t_token **token_list, char *input);
void	m_get_new_token(t_automat *aut, t_token **token_list, char *input);

//Automaton functions
int		m_is_special_char(char c);
int		m_get_next_status(int status, char c);
int		m_get_status_1(char c);
int		m_get_status_40(char c);
int		m_get_status_60(char c);
int		m_get_status_70(char c);
int		m_get_status_80(char c);
int		m_get_status_81(char c);
int		m_get_status_82(char c);
int		m_is_final_status(int status);
int		m_status_needs_backtrack(int status);
int		m_get_token_type(int status);

//Token List functions
t_token	*m_create_token(char *lexeme, int type);
t_token	*m_find_last_token(t_token *token_ptr);
void	m_add_token(t_token **token_list, t_token *new_token);
void	m_free_tokens(t_token **tokens);
void	free_cmd_array(char **command);
int		m_validate_tokens(t_token *tokens);

#endif
