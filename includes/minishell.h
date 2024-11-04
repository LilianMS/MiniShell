#ifndef MINISHELL_H
# define MINISHELL_H

// Libs
# include "tokenizer.h"
# include "parser.h"

# include "../libs/libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

//Structs
typedef struct s_mini		t_mini;
typedef struct s_token		t_token;
typedef struct s_env		t_env;

struct s_mini
{
	char	*line;
	t_env	*env_list;
};

// Lexical Analysis Functions
void	m_lexical_analysis(t_mini mini);
int		ft_check_quotes(const char *line);
char	*m_clean_quotes(char *lexeme);

// Parsing Functions
t_token	*m_parse_tokens(t_token **token_list, t_token **parsed_list);

#endif
