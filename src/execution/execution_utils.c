#include "../../includes/minishell.h"

void	m_free_everything(t_mini *mini)
{
	if (mini->line)
		free(mini->line);
	if (mini->env_list)
		m_free_env_list(mini->env_list);
	if (mini->tree)
		m_tree_cleaner(mini->tree);
	if (mini->hdoc->filename)
		free(mini->hdoc->filename);
	if (mini->hdoc)
		free(mini->hdoc);
	m_close_fds(mini);
}

int	m_count_non_empty_strings(char **cmd_array)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd_array[i] != NULL)
	{
		if (cmd_array[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

int	m_fill_cleaned_array(char **cmd_array, char **cleaned_array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_array[i] != NULL)
	{
		if (cmd_array[i][0] != '\0')
		{
			cleaned_array[j] = ft_strdup(cmd_array[i]);
			if (!cleaned_array[j])
			{
				while (j > 0)
					free(cleaned_array[--j]);
				free(cleaned_array);
				return (0);
			}
			j++;
		}
		i++;
	}
	cleaned_array[j] = NULL;
	return (1);
}

char	**m_remove_empty_strings(char **cmd_array)
{
	char	**cleaned_array;
	int		count;

	count = m_count_non_empty_strings(cmd_array);
	cleaned_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!cleaned_array)
		return (NULL);
	if (!m_fill_cleaned_array(cmd_array, cleaned_array))
		return (NULL);
	return (cleaned_array);
}

int	m_prepare_command(char **tree_node_cmd, char ***cleaned_cmd_array, t_mini *mini)
{
	if (tree_node_cmd[0][0] == '\0' && !tree_node_cmd[1] && mini->expand_empty)
		return (0);
	else
		*cleaned_cmd_array = m_remove_empty_strings(tree_node_cmd);
	if (!*cleaned_cmd_array)
		return (0);
	return (1);
}