#include "../includes/minishell.h"

int main()
{
	t_token	*tokens;
	char	*input;

	input = "ls -l | grep .c";
	tokens = m_tokenize(input);
	
	print_tokens(tokens); // ------- Debug
	
	m_free_tokens(tokens);
	return 0;
}