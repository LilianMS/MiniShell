#ifndef MINISHELL_H
# define MINISHELL_H

// Libs
# include "../libs/libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>

# include "tokenizer.h"
# include "parser.h"
# include "ast.h"
# include "execution.h"
# include "builtin.h"

# define LLONG_MAX 9223372036854775807LL
#define PINK_BOLD "\033[1;35m"
#define CYAN_BOLD "\033[1;36m"
#define RESET "\033[0m"

extern volatile sig_atomic_t	g_signal_status;

//Structs
typedef struct s_mini			t_mini;
typedef struct s_token			t_token;
typedef struct s_env			t_env;
typedef struct s_tree			t_tree;
typedef struct s_hdoc			t_hdoc;
typedef struct termios			t_termios;

struct s_mini
{
	char			*line;
	int				backup_fd_in;
	int				exit_status;
	int				expand_empty;
	pid_t			current_pid;
	t_env			*env_list;
	t_tree			*tree;
	t_hdoc			*hdoc;
	t_termios		term;
};

struct s_hdoc
{
	char			*delimiter;
	char			*filename;
	char			*history_block;
	int				temp_fd;
	int				exit_flag;
	int				suffix_doc;
	long long int	nb_line_del;
};

// Init functions
void				init_minishell(t_mini *mini, char **envp);
void				update_mini(t_mini *mini);
void				m_init_signals(void);
int					m_is_input_null(t_mini *mini);
int					m_minishell_on(t_mini *mini);
long long int		m_update_nb_lines(long long int num);

// Lexical Analysis Functions
t_token				*m_lexical_analysis(t_mini *mini);
int					m_check_line_input(const char *line);
char				*m_clean_qts(char *lexeme);
void				m_sig_int(int signum);
t_token				*m_parse_tokens(t_token **token_list, \
						t_token **parsed_list, t_mini *mini);
void				m_exec_signals(int pid);

// Heredoc functions
int					m_heredoc( t_token **parsed_list, t_mini *mini);
void				heredoc_signals(void);
void				m_aux_heredoc(t_hdoc *hdoc, t_token *node, t_mini *mini);
int					heredoc_create_file(t_hdoc **hdoc);
void				m_heredoc_delete_files(t_mini *mini);
void				print_heredoc_message(t_hdoc *hdoc);

#endif
