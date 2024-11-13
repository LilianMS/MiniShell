#include "../includes/ast.h"

// void	list_printer(t_token *list)
// {
// 	int list_len;
// 	t_token *curr;

// 	curr = list;
// 	list_len = list_size(list);
// 	fprintf(stderr, "List size: %d\n", list_len);
// 	fprintf(stderr, "List content:\n");
// 	fprintf(stderr, "|-----|---------------|------|----------------|----------------|----------------|\n");
// 	fprintf(stderr, "| pos |    content    | type |      prev      |      curr      |      next      |\n");
// 	fprintf(stderr, "|-----|---------------|------|----------------|----------------|----------------|\n");
// 	while (curr)
// 	{
// 		fprintf(stderr, "| %8d | %13s | %4d | %2p   | %2p | %2p   |\n", curr->position, curr->content, curr->type, curr->prev, curr, curr->next);
// 		curr = curr->next;
// 	}
// 	fprintf(stderr, "|-----|---------------|------|----------------|----------------|----------------|\n\n");
// 	fflush(stderr);
// }