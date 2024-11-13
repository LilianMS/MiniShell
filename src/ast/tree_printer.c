#include "../includes/ast.h"

// static void	print_tree(t_tree *root, int distance, t_var_types type);

// void print_env_copy(char **copy)
// {
// 	int i;

// 	i = 0;
// 	if (copy == NULL)
// 		printf("array envcopy vazio\n");
// 	while (copy[i])
// 	{
// 		printf("env_copy: %s\n", copy[i]);
// 		i++;
// 	}
// }


// void		visualize_tree(t_tree *root, t_var_types type)
// {
// 	printf(CYAN "Tree visualization:\n\n\n" RESET);
// 	print_tree(root, 0, type);
// 	printf("\n\n");
// }

// static void	print_tree(t_tree *root, int distance, t_var_types type)
// {
// 	if (root == NULL)
// 		return ;
// 	distance += SPACES;
// 	print_tree(root->right, distance, type);
// 	print_right_branch(distance + 2, root->right);
// 	print_item(root, type, distance);
// 	print_left_branch(distance + 2, root->left);
// 	print_tree(root->left, distance, type);
// }
// void	print_distance(int distance)
// {
// 	for (int i = SPACES; i < distance; i++)
// 		printf(" ");
// }

// void print_right_branch(int distance, t_tree *right)
// {
// 	if (!right)
// 		return ;
// 	print_distance(distance);
//     printf("/\n");
// }

// void print_left_branch(int distance, t_tree *left)
// {
// 	if (!left)
// 		return ;
// 	print_distance(distance);
//     printf("\\\n");
// }

// void	print_item(t_tree *this_node, t_var_types type, int distance)
// {
// 	print_distance(distance);
// 	if (INT == type)
// 		printf("%d\n", *(int *)this_node->item);
// 	else if (CHAR == type)
// 		printf("%s\n", (char *)this_node->item);
// }