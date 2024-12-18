#include "../../includes/minishell.h"

// void	m_execute_command(t_tree *tree)
// {
	
// }

void	m_execution(t_mini *mini, t_token **parsed_list)
{
	if (!mini->tree)
		return ;
	if (mini->tree->type == COMMAND)
	{
		if (m_is_builtin(mini->tree) != -1)
			m_execute_builtin(mini, parsed_list);
		// else
		// 	m_execute_command(tree);
	}
	// else
	// {
	// 	m_execution(tree->left);
	// 	m_execution(tree->right);
	// }
}
