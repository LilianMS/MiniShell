#ifndef MINISHELL_H
# define MINISHELL_H

// Libs
# include "../libs/libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

# include "tokenizer.h"
# include "parser.h"

extern volatile sig_atomic_t	g_signal_status;

//Structs
typedef struct s_mini	t_mini;
typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_tree	t_tree;
typedef struct s_hdoc	t_hdoc; // temporario para heredoc

struct s_mini
{
	char	*line;
	t_env	*env_list;
	t_tree	*tree;
	t_hdoc	*hdoc; // temporario para heredoc
} ;

struct s_hdoc
{
	char	*cmd;
	int		temp_fd;
	char	*delimiter;
	int		exit_flag;
	t_env	*env_list;
	t_token	*parsed_list;
} ;

// Lexical Analysis Functions
void	m_lexical_analysis(t_mini *mini);
char	*m_clean_quotes(char *lexeme);
int		m_check_line_input(const char *line);
void	init_minishell(t_mini *mini, char **envp);
void	m_sig_int(int signum);
int		m_is_input_null(t_mini *mini);

// Parsing Functions
t_token	*m_parse_tokens(t_token **token_list, t_token **parsed_list, t_env *env_list);

// heredoc functions
void	m_heredoc(t_token **parsed_list, t_mini mini);
void	m_aux_heredoc(t_hdoc *hdoc);
char	*m_heredoc_get_delimiter(t_token *parsed_list);
void	m_heredoc_update_command_list(t_token **parsed_list, t_hdoc *hdoc);

// g_signal_status
char	*m_get_exit_status(void);
void	m_update_exit_status(int code_exit);

#endif
