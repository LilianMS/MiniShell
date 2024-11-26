#include "../includes/debug.h"

static void	print_tree(t_tree *root, int distance);

void		visualize_tree(t_tree *root)
{
	printf(CYAN "Tree visualization:\n\n\n" RESET);
	print_tree(root, 0);
	printf("\n\n");
}

static void	print_tree(t_tree *root, int distance)
{
	if (root == NULL)
		return ;
	distance += SPACES;
	print_trINTee(root->right, distance);
	print_right_branch(distance + 2, root->right);
	print_item(root, distance);
	print_left_branch(distance + 2, root->left);
	print_tree(root->left, distance);
}
void	print_distance(int distance)
{
	for (int i = SPACES; i < distance; i++)
		printf(" ");
}

void	print_right_branch(int distance, t_tree *right)
{
	if (!right)
		return ;
	print_distance(distance);
    printf("/\n");
}

void	print_left_branch(int distance, t_tree *left)
{
	if (!left)
		return ;
	print_distance(distance);
    printf("\\\n");
}

void	print_item(t_tree *this_node, int distance)
{
	print_distance(distance);
	printf("%s\n", this_node->content);
}