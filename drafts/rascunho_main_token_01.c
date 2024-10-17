#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definindo os tipos de tokens
typedef enum e_token_type
{
    CMD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND
} t_token_type;

// Estrutura do token
typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

// Funções auxiliares da libft

size_t ft_strlen(const char *s)
{
    size_t len = 0;

    if (!s)
        return 0;
    while (s[len])
        len++;
    return len;
}

char *ft_strdup(const char *s)
{
    char *dst;
    dst = malloc(ft_strlen(s) + 1);
    if (dst == NULL)
        return NULL;
    strcpy(dst, s);
    return dst;
}

char *ft_strndup(const char *s, size_t n)
{
    char *dst;
    dst = malloc(n + 1);
    if (!dst)
        return NULL;
    strncpy(dst, s, n);
    dst[n] = '\0';  // Certifique-se de que a string resultante seja terminada em '\0'
    return dst;
}

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

char *ft_strcat(char *dest, const char *src)
{
    size_t i = 0;
    size_t j = 0;

    // Encontra o final da string 'dest'
    while (dest[i] != '\0')
        i++;

    // Concatena 'src' no final de 'dest'
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';  // Adiciona o terminador nulo no final

    return dest;
}

int ft_isspace(char c)
{
    return isspace(c);
}

// Funções relacionadas aos tokens

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
    token->value = ft_strdup(value);
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
    while (input[*i] && ft_isspace(input[*i]))
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
    return ft_strndup(&input[start], (*i) - start - 1);  // Retorna o conteúdo entre aspas
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
    var_name = ft_strndup(&input[start], (*i) - start);
    var_value = getenv(var_name); // Obtém o valor da variável de ambiente
    free(var_name);
    if (var_value)
        return ft_strdup(var_value);
    else
        return ft_strdup(""); // Retorna string vazia se a variável não existir
}

// a partir daqui são funções auxiliares para m_process_word

char *append_substring(char *word, char *input, int start, int end)
{
    char *substring = ft_strndup(&input[start], end - start);
    word = ft_realloc(word, ft_strlen(word) + ft_strlen(substring) + 1);
    ft_strcat(word, substring);
    free(substring);
    return word;
}

char *process_quotes(char *input, int *i, char *word, int start)
{
    char *quoted_word;
    if (*i > start)
        word = append_substring(word, input, start, *i);

    quoted_word = m_handle_quotes(input, i);
    word = ft_realloc(word, ft_strlen(word) + ft_strlen(quoted_word) + 1);
    ft_strcat(word, quoted_word);
    free(quoted_word);

    return word;
}

char *process_expansion(char *input, int *i, char *word, int start)
{
    char *expanded_word;
    if (*i > start)
        word = append_substring(word, input, start, *i);

    expanded_word = m_handle_expansion(input, i);
    word = ft_realloc(word, ft_strlen(word) + ft_strlen(expanded_word) + 1);
    ft_strcat(word, expanded_word);
    free(expanded_word);

    return word;
}


char *process_remaining_word(char *input, int *i, char *word, int start)
{
    if (start < *i) {
        word = append_substring(word, input, start, *i);
    }
    return word;
}

void m_process_word(char *input, int *i, t_token **tokens)
{
    char *word = NULL;
    int start = *i;

    while (input[*i] && !ft_isspace(input[*i]) && !m_is_special_char(input[*i]))
    {
        if (input[*i] == '\'' || input[*i] == '\"')
            word = process_quotes(input, i, word, start);
        else if (input[*i] == '$')
            word = process_expansion(input, i, word, start);
        else
            (*i)++;
    }

    word = process_remaining_word(input, i, word, start);
    m_add_token(tokens, m_create_token(word, CMD));
    free(word);
}


/*

// Função para processar palavras
void m_process_word(char *input, int *i, t_token **tokens)
{
    char *word = NULL;
    char *quoted_word;
    char *expanded_word;
    int start = *i;

    while (input[*i] && !ft_isspace(input[*i]) && !m_is_special_char(input[*i]))
    {
        if (input[*i] == '\'' || input[*i] == '\"')
        {
            // Parte antes das aspas
            if (*i > start)
                word = ft_strndup(&input[start], *i - start);
            // Processa o conteúdo entre aspas
            quoted_word = m_handle_quotes(input, i);
            word = ft_realloc(word, ft_strlen(word) + ft_strlen(quoted_word) + 1);
            ft_strcat(word, quoted_word);
            free(quoted_word);
            start = *i;  // Atualiza o início após as aspas
        }
        else if (input[*i] == '$')
        {
            // Parte antes da expansão
            if (*i > start)
                word = ft_strndup(&input[start], *i - start);
            // Expande a variável
            expanded_word = m_handle_expansion(input, i);
            word = ft_realloc(word, ft_strlen(word) + ft_strlen(expanded_word) + 1);
            ft_strcat(word, expanded_word);
            free(expanded_word);
            start = *i;  // Atualiza o início após a expansão
        }
        else
            (*i)++;  // Continua avançando
    }

    if (start < *i) {
        char *remaining_word = ft_strndup(&input[start], *i - start);
        word = ft_realloc(word, ft_strlen(word) + ft_strlen(remaining_word) + 1);
        ft_strcat(word, remaining_word);
        free(remaining_word);
    }

    m_add_token(tokens, m_create_token(word, CMD));
    free(word);
}
*/



// Função principal de tokenização
t_token *m_tokenize(char *input)
{
    t_token *tokens = NULL;
    int i = 0;

    while (input[i])
    {
        m_skip_whitespace(input, &i);
        if (m_is_special_char(input[i]))
            m_process_operator(input, &i, &tokens);
        else if (input[i])
            m_process_word(input, &i, &tokens);
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
    char *input = "ls -l | grep .c";

    tokens = m_tokenize(input);

    print_tokens(tokens);
    m_free_tokens(tokens);
    
    return 0;
}


/*
até aqui erro de contexto:

==8167== Memcheck, a memory error detector
==8167== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==8167== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==8167== Command: ./a.out
==8167== 
==8167== Conditional jump or move depends on uninitialised value(s)
==8167==    at 0x1093BE: ft_strcat (in /home/lilian/Documents/projeto-minishell/mvp/src/a.out)
==8167==    by 0x109996: append_substring (in /home/lilian/Documents/projeto-minishell/mvp/src/a.out)
==8167==    by 0x109B5D: process_remaining_word (in /home/lilian/Documents/projeto-minishell/mvp/src/a.out)
==8167==    by 0x109C97: m_process_word (in /home/lilian/Documents/projeto-minishell/mvp/src/a.out)
==8167==    by 0x109D72: m_tokenize (in /home/lilian/Documents/projeto-minishell/mvp/src/a.out)
==8167==    by 0x109E1D: main (in /home/lilian/Documents/projeto-minishell/mvp/src/a.out)
==8167== 
Token: ls (Type: 0)
Token: -l (Type: 0)
Token: | (Type: 1)
Token: grep (Type: 0)
Token: .c (Type: 0)
==8167== 
==8167== HEAP SUMMARY:
==8167==     in use at exit: 0 bytes in 0 blocks
==8167==   total heap usage: 19 allocs, 19 frees, 1,188 bytes allocated
==8167== 
==8167== All heap blocks were freed -- no leaks are possible
==8167== 
==8167== Use --track-origins=yes to see where uninitialised values come from
==8167== For lists of detected and suppressed errors, rerun with: -s
==8167== ERROR SUMMARY: 4 errors from 1 contexts (suppressed: 0 from 0)

*/