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
# include <termios.h>

#include "tokenizer.h"
#include "parser.h"
#include "debug.h"
#include "ast.h"
#include "execution.h"
#include "builtin.h"

extern volatile sig_atomic_t	g_signal_status;

//Structs
typedef struct s_mini			t_mini;
typedef struct s_token			t_token;
typedef struct s_env			t_env;
typedef struct s_tree			t_tree;
typedef struct s_hdoc			t_hdoc; // novo
typedef struct termios			t_termios; // novo

struct s_mini
{
	char						*line;
	int							exit_status;
	int							backup_fd_in; // novo
	t_env						*env_list;
	t_tree						*tree;
	t_hdoc						*hdoc; // novo
	t_termios					term; // novo
};

struct s_hdoc
{
	char						*cmd;
	char						*delimiter;
	char						*filename;
	int							temp_fd;
	int							exit_flag;
	int							suffix_doc;
	t_env						*env_list;
};

// Lexical Analysis Functions
t_token							*m_lexical_analysis(t_mini *mini);
char							*m_clean_quotes(char *lexeme);
int								m_check_line_input(const char *line);
void							init_minishell(t_mini *mini, char **envp);
void							m_sig_int(int signum);
int								m_is_input_null(t_mini *mini);

// Parsing Functions
t_token							*m_parse_tokens(t_token **token_list, t_token **parsed_list, t_env *env_list);

void							m_exec_signals(int pid);

int								m_heredoc(t_tree *node, t_mini *mini);
void							m_aux_heredoc(t_hdoc *hdoc, t_tree *node);
void							m_heredoc_delete_files(t_mini *mini);

#endif
