#ifndef MINISHELL_H
# define MINISHELL_H

// Libs
# include "tokenizer.h"

# include "../libs/libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

//Structs
typedef struct s_mini		t_mini;
typedef struct s_token		t_token;

struct s_mini
{
	char	*input;
};

// Lexical Analysis Functions
void	m_lexical_analysis(char *line);
int		ft_check_quotes(const char *line);

//Debug Functions
void	print_tokens(t_token **tokens);

// Parsing Functions
t_token	*m_parse_tokens(t_token **token_list, t_token **parsed_list);

#endif