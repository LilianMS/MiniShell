### Definir os Tipos de Tokens

Primeiro, definir os tipos de tokens que seu shell precisará identificar. Esses tokens incluem:

- [ ] Comandos e Argumentos (e.g., ls, -la)
- [x] Redirecionadores (>, >>, <)
- [x] Pipes (|)
- [x] Aspas Simples e Duplas (para lidar com strings com espaços ou caracteres especiais)
- [ ] Variáveis de Ambiente ($VAR)
- [ ] Parênteses (se forem suportados)

### Passos da tokenização:

- [ ] Ignorar espaços em branco.
- [ ] Identificar o início de um token: se encontrar um símbolo especial como |, >, <, o token será um operador; se for uma letra ou $, pode ser um comando, argumento ou variável de ambiente.
- [ ] Gerar os tokens.
- [ ] Tratar aspas: Strings entre aspas simples (') ou duplas (") devem ser tratadas como um único token.
- [ ] Adicionar o token à lista.

