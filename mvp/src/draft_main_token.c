#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definindo os tipos de tokens
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
} t_token_type;

// Estrutura do token
typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next; // Para formar uma lista encadeada de tokens
}   t_token;

char *ft_realloc(char *ptr, size_t new_size)
{
    char *new_ptr = realloc(ptr, new_size);
    if (!new_ptr)
    {
        free(ptr);
        return NULL;
    }
    return new_ptr;
}

void m_free_tokens(t_token *tokens)
{
    t_token *current;
    t_token *next;

    current = tokens;
    while (current != NULL)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

t_token *m_create_token(char *value, t_token_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = strdup(value);
    token->type = type;
    token->next = NULL;
    return token;
}

void m_add_token(t_token **token_list, t_token *new_token)
{
    t_token *temp;

    if (!*token_list)
        *token_list = new_token;
    else
    {
        temp = *token_list;
        while (temp->next)
            temp = temp->next;
        temp->next = new_token;
    }
}

// Função para verificar caracteres especiais
int m_is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

// Função para pular espaços em branco
void m_skip_whitespace(char *input, int *i)
{
    while (input[*i] && isspace(input[*i]))
        (*i)++;
}

// Função para processar operadores
void m_process_operator(char *input, int *i, t_token **tokens)
{
    if (input[*i] == '|')
    {
        m_add_token(tokens, m_create_token("|", PIPE));
        (*i)++;
    }
    else if (input[*i] == '>')
    {
        if (input[*i + 1] == '>')
        {
            m_add_token(tokens, m_create_token(">>", REDIR_APPEND));
            (*i) += 2;
        }
        else
        {
            m_add_token(tokens, m_create_token(">", REDIR_OUT));
            (*i)++;
        }
    }
    else if (input[*i] == '<')
    {
        m_add_token(tokens, m_create_token("<", REDIR_IN));
        (*i)++;
    }
}

// Função para tratar aspas em palavras
char *m_handle_quotes(char *input, int *i)
{
    char quote;
    int start;

    quote = input[*i];
    start = ++(*i);  // Avança após a aspa
    while (input[*i] && input[*i] != quote)
        (*i)++;
    if (input[*i] == quote)  // Fecha a aspa
        (*i)++;
    return strndup(&input[start], (*i) - start - 1);  // Retorna o conteúdo entre aspas
}

// Função para tratar expansões de variáveis
char *m_handle_expansion(char *input, int *i)
{
    char *var_name;
    char *var_value;
    int start;

    start = ++(*i); // Avança após o '$'
    while (input[*i] && (isalnum(input[*i]) || input[*i] == '_'))
        (*i)++;
    var_name = strndup(&input[start], (*i) - start);
    var_value = getenv(var_name); // Obtém o valor da variável de ambiente
    free(var_name);
    if (var_value)
        return strdup(var_value);
    else
        return strdup(""); // Retorna string vazia se a variável não existir
}

char *append_substring(char *word, char *input, int start, int end)
{
    char *substring = strndup(&input[start], end - start);
    if (!substring) 
        return NULL;

    word = ft_realloc(word, strlen(word) + strlen(substring) + 1);
    if (!word) 
    {
        free(substring);
        return NULL;
    }

    strcat(word, substring);
    free(substring);
    return word;
}

char *process_expansion(char *input, int *i, char *word, int start)
{
    char *expanded_word;
    if (*i > start)
        word = append_substring(word, input, start, *i);

    expanded_word = m_handle_expansion(input, i);
    word = ft_realloc(word, strlen(word) + strlen(expanded_word) + 1);
    if (!word) 
        return NULL;
    strcat(word, expanded_word);
    free(expanded_word);

    return word;
}

char *process_quotes(char *input, int *i, char *word, int start)
{
    char *quoted_word;
    if (*i > start)
        word = append_substring(word, input, start, *i);

    quoted_word = m_handle_quotes(input, i);
    word = ft_realloc(word, strlen(word) + strlen(quoted_word) + 1);
    if (!word) 
        return NULL;
    strcat(word, quoted_word);
    free(quoted_word);

    return word;
}

char *process_remaining_word(char *input, int *i, char *word, int start)
{
    if (start < *i) {
        word = append_substring(word, input, start, *i);
    }
    return word;
}

void m_process_word(char *input, int *i, t_token **tokens, int is_first)
{
    char *word = strdup(""); 
    int start = *i;

    while (input[*i] && !isspace(input[*i]) && !m_is_special_char(input[*i]))
    {
        if (input[*i] == '\'' || input[*i] == '\"')
            word = process_quotes(input, i, word, start);
        else if (input[*i] == '$')
            word = process_expansion(input, i, word, start);
        else
            (*i)++;
    }

    word = process_remaining_word(input, i, word, start);
    t_token_type type = is_first ? CMD : ARG;
    m_add_token(tokens, m_create_token(word, type));
    free(word);
}

// Função principal de tokenização
t_token *m_tokenize(char *input)
{
    t_token *tokens = NULL;
    int i = 0;
    int is_first = 1;

    while (input[i])
    {
        m_skip_whitespace(input, &i);
        if (m_is_special_char(input[i]))
        {
            m_process_operator(input, &i, &tokens);
            is_first = 1; // Reinicia após operadores
        }
        else if (input[i])
        {
            m_process_word(input, &i, &tokens, is_first);
            is_first = 0;
        }
    }

    return tokens;
}

// Função para imprimir tokens
void print_tokens(t_token *tokens)
{
    t_token *current = tokens;
    while (current)
    {
        printf("Token: %s (Type: %d)\n", current->value, current->type);
        current = current->next;
    }
}

// Função principal de teste
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
