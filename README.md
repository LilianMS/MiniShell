<hr>

<p align="right">
  <a href="#-minishell">🇺🇸</a> | <a href="#-minishell-em-português">🇧🇷</a>
</p>

# 🐚 Minishell
**Minishell** is a project developed at 42 São Paulo with the goal of recreating a minimalist shell, capable of interpreting and executing commands in a terminal — just like Bash.

This is one of the most challenging and fundamental projects in the 42 core curriculum, requiring a deep understanding of process management, memory handling, data structures, and command interpretation.

Built in collaboration: [@Letícia Sampietro](https://github.com/lesampietro) and [@Lilian Mendes](https://github.com/LilianMS).

---

## 🚀 Project Goals

- Implement a fully functional shell that supports:
  - Execution of system and built-in commands (e.g., `ls`, `echo`, `cat`, etc.);
  - Pipes (`|`) and redirections (`<`, `>`, `>>`, `<<`);
  - Proper handling of exit codes and error management;
- Handle a wide variety of user inputs, including invalid and edge cases;
- Build built-in commands (`cd`, `exit`, `env`, `export`, etc.) to be executed by the program;

---

## 🧠 Key Concepts Implemented

### 1. Initial Validation
- Basic error handling and input validation before processing the command line.

### 2. Tokenization
- Input is broken into tokens using a **finite state machine**.
- Each token is stored as a node in a **doubly linked list**, representing commands, arguments, or operators (pipes, redirects...).

### 3. Parsing
- Semantic analysis of the token list, including:
  - Handling of single and double quotes
  - Commands + Arguments grouping
  - Processing of pipes and redirects, including heredoc

### 4. Abstract Syntax Tree (AST)
- Tokens are organized into a **binary tree**, where:
  - Each node represents a command, operator, or redirection
  - Execution begins recursively from the leftmost node

### 5. Execution
- Recursive traversal of the AST:
  - Each node is evaluated as a simple command, pipe, redirection, or builtin
  - Uses `fork()`, `execve()`, and `pipe()` to manage processes
  - Ensures correct return codes and cleanup after execution

---


<p align="right">
  <a href="#-minishell">🇺🇸</a> | <a href="#-minishell-em-português">🇧🇷</a>
</p>

# 🐚 Minishell em português

**Minishell** é um projeto desenvolvido na 42 São Paulo com o objetivo de recriar um shell minimalista, capaz de interpretar e executar comandos no terminal — assim como o Bash.

Esse é um dos projetos mais desafiadores e fundamentais do currículo da 42, exigindo profundo entendimento de gerenciamento de processos, manipulação de memória, estruturas de dados e interpretação de comandos.

Desenvolvido em colaboração: [@Letícia Sampietro](https://github.com/lesampietro) e [@Lilian Mendes](https://github.com/LilianMS).

---

## 🚀 Objetivos do Projeto

- Implementar um shell totalmente funcional com suporte a:
  - Execução de comandos do sistema e comandos internos (como `ls`, `echo`, `cat`, etc.);
  - Pipes (`|`) e redirecionamentos (`<`, `>`, `>>`, `<<`);
  - Tratamento correto de códigos de saída e gerenciamento de erros;
- Tratar uma ampla variedade de entradas do usuário, incluindo casos inválidos e extremos;
- Construir comandos internos (`cd`, `exit`, `env`, `export`, etc.) executados diretamente pelo programa;

---

## 🧠 Conceitos-Chave Implementados

### 1. Validação Inicial
- Tratamento básico de erros e validação de entrada antes do processamento da linha de comando.

### 2. Tokenização
- A entrada é dividida em tokens usando uma **máquina de estados finita**.
- Cada token é armazenado como um nó em uma **lista duplamente encadeada**, representando comandos, argumentos ou operadores (pipes, redirecionamentos...).

### 3. Análise Sintática
- Análise semântica da lista de tokens, incluindo:
  - Tratamento de aspas simples e duplas
  - Agrupamento de comandos + argumentos
  - Processamento de pipes e redirecionamentos, incluindo heredoc

### 4. Árvore de Sintaxe Abstrata (AST)
- Tokens são organizados em uma **árvore binária**, onde:
  - Cada nó representa um comando, operador ou redirecionamento
  - A execução começa recursivamente pelo nó mais à esquerda

### 5. Execução
- Percurso recursivo da AST:
  - Cada nó é avaliado como um comando simples, pipe, redirecionamento ou builtin
  - Utiliza `fork()`, `execve()` e `pipe()` para gerenciar processos
  - Garante códigos de retorno corretos e limpeza de recursos após a execução

---
