#include "minishell.h"

int main()
{
	t_token *tokens;

	// Caso 1: Comando simples
	char *input1 = "ls -l /home";
	printf("Input: %s\n", input1);
	tokens = m_tokenize(input1);
	print_tokens(tokens);
	m_free_tokens(tokens);
	printf("\n");

	// Caso 2: Comando com pipe
	char *input2 = "ls -l | grep .c";
	printf("Input: %s\n", input2);
	tokens = m_tokenize(input2);
	print_tokens(tokens);
	m_free_tokens(tokens);
	printf("\n");

	// Caso 3: Redirecionamento de entrada e saída
	char *input3 = "cat < input.txt > output.txt";
	printf("Input: %s\n", input3);
	tokens = m_tokenize(input3);
	print_tokens(tokens);
	m_free_tokens(tokens);
	printf("\n");

	// Caso 4: Redirecionamento de append
	char *input4 = "echo \"Hello World\" >> output.txt";
	printf("Input: %s\n", input4);
	tokens = m_tokenize(input4);
	print_tokens(tokens);
	m_free_tokens(tokens);
	printf("\n");

	// Caso 5: Comando com variável de ambiente
	char *input5 = "echo $USER";
	printf("Input: %s\n", input5);
	tokens = m_tokenize(input5);
	print_tokens(tokens);
	m_free_tokens(tokens);
	printf("\n");

	// Caso 6: Comando com aspas simples e duplas
	char *input6 = "echo 'Single quote test' \"Double quote test\"";
	printf("Input: %s\n", input6);
	tokens = m_tokenize(input6);
	print_tokens(tokens);
	m_free_tokens(tokens);
	printf("\n");

	// Caso 7: Comando complexo com pipes, redirecionamento e variáveis
	char *input7 = "grep $USER < input.txt | wc -l > output.txt";
	printf("Input: %s\n", input7);
	tokens = m_tokenize(input7);
	print_tokens(tokens);
	m_free_tokens(tokens);
	printf("\n");

	// Caso 8: Comando vazio (só espaços em branco)
	char *input8 = "   ";
	printf("Input: \"%s\"\n", input8);
	tokens = m_tokenize(input8);
	print_tokens(tokens);
	m_free_tokens(tokens);
	printf("\n");

	return 0;
}
