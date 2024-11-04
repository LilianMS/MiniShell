# MINISHELL

[![](https://img.shields.io/badge/%20São%20Paulo-000000?style=for-the-badge&logo=42&logoColor=white)](https://www.42sp.org.br/)

_common core project_

---


##

## Dicas:

### :octocat: Comandos Git:

#### Para ver resumo de mudanças do último commit:

```git show --stat```

```git log -p -1```


#### Adicionar mudanças ao último commit ou editá-lo:

```

git add <arquivo>

git commit --amend

git push --force

```

### Exemplos de commit

:pencil: draft: m_tokenize and todo_notes.md

:sparkles: feat: add ft_strndup in Libft

:broom: cleanup: remove redundant lines

:boom: fix: não tínhamos dado git push nessas alterações

:bug: bug: correct makefile

:books: docs: update README


### Para testar com o valgrind sem os leaks do readline:

> ``` valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell ```

