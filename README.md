# 🐚 Minishell

**Minishell** is a project developed at 42 São Paulo with the goal of recreating a minimalist shell, capable of interpreting and executing commands in a terminal — just like Bash.

This is one of the most challenging and fundamental projects in the 42 core curriculum, requiring a deep understanding of process management, memory handling, data structures, and command interpretation.

Built in collaboration with [@Lilian](https://github.com/LilianMS).

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
