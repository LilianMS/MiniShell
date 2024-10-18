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

