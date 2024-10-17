# 	TODO

### Definir os Tipos de Tokens

Primeiro, definir os tipos de tokens que seu shell precisará identificar. Esses tokens incluem:

- [ ] Comandos e Argumentos (e.g., ls, -la)
- [x] Redirecionadores (>, >>, <)
- [x] Pipes (|)
- [x] Aspas Simples e Duplas (para lidar com strings com espaços ou caracteres especiais)
- [x] Variáveis de Ambiente ($VAR)
- [ ] Parênteses (se forem suportados)

### Passos da tokenização:

- [x] Ignorar espaços em branco.
- [x] Identificar o início de um token: se encontrar um símbolo especial como |, >, <, o token será um operador; se for uma letra ou $, pode ser um comando, argumento ou variável de ambiente.
- [x] Gerar os tokens.
- [x] Tratar aspas: Strings entre aspas simples (') ou duplas (") devem ser tratadas como um único token.
- [x] Adicionar o token à lista.
- [ ] implementar << heredoc

# Notas

- Novas funções:
	- void	m_free_tokens(t_token *tokens);
	- t_token	*m_create_token(char *value, t_token_type type);
	- void	m_add_token(t_token **token_list, t_token *new_token);
	- int	m_is_special_char(char c);
	- t_token	*m_tokenize(char *input);

- Refatorar e/ou completar:
	- Função m_tokenize();

- Implementar:
	- aspas;
	- $ - Expansão de variáveis;

- Testes simples:
	- void	print_tokens(t_token *tokens);