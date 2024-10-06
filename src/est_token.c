/* Para criar uma forma de identificar e separar diferentes tipos de tokens em C sem usar bibliotecas externas, você pode usar uma combinação de `strtok` e uma estrutura de dados para definir os tipos de tokens. Aqui está um exemplo básico:

1. Defina uma enumeração para os tipos de tokens.
2. Crie uma estrutura para armazenar o token e seu tipo.
3. Implemente uma função para identificar e separar os tokens com base em seus tipos.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_WORD,
    TOKEN_NUMBER,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[50];
} Token;

TokenType identifyTokenType(const char *token) {
    if (isdigit(token[0])) {
        return TOKEN_NUMBER;
    } else if (isalpha(token[0])) {
        return TOKEN_WORD;
    } else {
        return TOKEN_UNKNOWN;
    }
}

void tokenize(const char *str, const char *delim) {
    char buffer[100];
    strcpy(buffer, str);
    
    char *tokenStr = strtok(buffer, delim);
    while (tokenStr != NULL) {
        Token token;
        token.type = identifyTokenType(tokenStr);
        strcpy(token.value, tokenStr);
        
        // Print the token and its type
        switch (token.type) {
            case TOKEN_WORD:
                printf("WORD: %s\n", token.value);
                break;
            case TOKEN_NUMBER:
                printf("NUMBER: %s\n", token.value);
                break;
            case TOKEN_UNKNOWN:
                printf("UNKNOWN: %s\n", token.value);
                break;
        }
        
        tokenStr = strtok(NULL, delim);
    }
}

int main() {
    const char *text = "hello,123,world,456";
    const char *delim = ",";
    tokenize(text, delim);
    return 0;
}

/*
Neste exemplo:
- `TokenType` enum define os diferentes tipos de tokens (palavras, números e desconhecidos).
- `Token` struct armazena o tipo e o valor do token.
- `identifyTokenType` identifica o tipo de um token.
- `tokenize` divide a string de entrada em tokens usando `strtok`, identifica o tipo de cada token e o imprime.

Você pode adaptar essa abordagem para suas necessidades específicas, adicionando mais tipos de tokens ou ajustando os critérios de identificação.
*/