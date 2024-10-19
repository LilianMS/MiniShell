

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/includes/libft.h"
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_mini	t_mini;

struct s_mini
{
	char	*input;
};

// Lexical Analysis Functions
int		m_check_quotes(const char *line);
void	m_lexical_analysis(char *line);

// Parsing Functions

#endif