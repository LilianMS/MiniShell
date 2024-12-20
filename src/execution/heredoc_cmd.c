#include "../../includes/minishell.h"

// manipula o ponteiro do arquivo temporário para o início, evitando o uso da função lseek
void	ft_reset_file_pointer(int *fd, const char *filename)
{
	close(*fd);
	*fd = open(filename, O_RDWR);
	if (*fd == -1)
	{
		perror("Error reopening file");
		exit(EXIT_FAILURE);
	}
}

// usa a biblioteca sys/stat (stat, lstat, fstat) para obter o tamanho do arquivo temporário e aloca memória para a string cmd
void	heredoc_read_fd_to_string(t_hdoc **hdoc)
{
	struct stat	st;
	ssize_t		read_size;

	if (fstat((*hdoc)->temp_fd, &st) == -1)
	{
		perror("Error getting file size");
		return ;
	}
	(*hdoc)->cmd = malloc(st.st_size + 1);
	if (!(*hdoc)->cmd)
	{
		perror("Error allocating memory");
		return ;
	}
	read_size = read((*hdoc)->temp_fd, (*hdoc)->cmd, st.st_size);
	if (read_size != st.st_size)
	{
		perror("Error reading file");
		free((*hdoc)->cmd);
		return ;
	}
	(*hdoc)->cmd[st.st_size] = '\0';
}

void	heredoc_alloc_new_cmd(char ***new_cmd, char **current_cmd, int i)
{
	int	j;

	*new_cmd = malloc(sizeof(char *) * (i + 2));
	if (!*new_cmd)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (j < i)
	{
		(*new_cmd)[j] = current_cmd[j];
		j++;
	}
}

void	m_heredoc_update_command_list(t_token **token_list, t_hdoc *hdoc)
{
	t_token	*new_token;

	ft_reset_file_pointer(&hdoc->temp_fd, ".heredoc_tmp");
	heredoc_read_fd_to_string(&hdoc);

	// adicionar um nó do tipo WORD com o conteúdo de hdoc->cmd

	new_token = m_create_token(hdoc->cmd, WORD);
	m_add_token(token_list, new_token);
	
}

// void	m_heredoc_update_command_list(t_token **parsed_list, t_hdoc *hdoc)
// {
// 	t_token	*current;
// 	char	**new_command;
// 	int		i;

// 	ft_reset_file_pointer(&hdoc->temp_fd, ".heredoc_tmp");
// 	heredoc_read_fd_to_string(&hdoc);
// 	current = *parsed_list;
// 	while (current)
// 	{
// 		if (current->type == COMMAND)
// 		{
// 			i = 0;
// 			while (current->command[i] != NULL)
// 				i++;
// 			heredoc_alloc_new_cmd(&new_command, current->command, i);
// 			free(current->command);
// 			current->command = new_command;
// 			current->command[i] = hdoc->cmd;
// 			current->command[i + 1] = NULL;
// 			break ;
// 		}
// 		current = current->next;
// 	}
// }
