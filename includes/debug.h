#ifndef DEBUG_H
# define DEBUG_H

# define SPACES 4
# define CYAN "\033[36m"
# define RESET "\033[0m"

//Libs
# include "minishell.h"
# include "parser.h"
# include "tokenizer.h"

//Structs
typedef struct s_token		t_token;
typedef struct s_env		t_env;

//functions to debug
void	print_parsed_tokens(t_token **tokens);
void	print_tokens(t_token **tokens);
void	list_printer(t_token **parsed_list);
int		list_size(t_token **parsed_list);
void	print_parsed_command(t_token *parsed_list);
void	print_char_array(char **array);

#endif

	// GETENV
	// Name of the environment variable (e.g., PATH)
	// const char *name = "HOME";
	// Get the value associated with the variable
	// const char *env_p = getenv(name);
	// if(env_p)
	// 	printf("Your %s is %s\n", name, env_p);