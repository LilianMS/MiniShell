#include "../../includes/minishell.h"

int	create_temp_file(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		perror("Error creating temp file");
	return (fd);
}

void	reset_file_pointer(int *fd, const char *filename)
{
	close(*fd);
	*fd = open(filename, O_RDWR);
	if (*fd == -1) {
		perror("Error reopening file");
		exit(EXIT_FAILURE);
	}
}

void	read_fd_to_string(t_hdoc **hdoc)
{
	struct stat	st;
	ssize_t		read_size;

	if (fstat((*hdoc)->temp_fd, &st) == -1)
	{
		perror("Error getting file size");
		return;
	}
	(*hdoc)->cmd = malloc(st.st_size + 1);
	if (!(*hdoc)->cmd)
	{
		perror("Error allocating memory");
		return;
	}
	read_size = read((*hdoc)->temp_fd, (*hdoc)->cmd, st.st_size);
	if (read_size != st.st_size)
	{
		perror("Error reading file");
		free((*hdoc)->cmd);
		return;
	}
	(*hdoc)->cmd[st.st_size] = '\0';
}

void	allocate_new_command(char ***new_command, char **current_command, int i)
{
	int	j;
	
	*new_command = malloc(sizeof(char *) * (i + 2));
	if (!*new_command)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (j < i)
	{
		(*new_command)[j] = current_command[j];
		j++;
	}
}

void update_command_list_with_temp_fd(t_token **parsed_list, t_hdoc *hdoc)
{
    t_token *current;
    int i;

    reset_file_pointer(&hdoc->temp_fd, ".heredoc_tmp");
    read_fd_to_string(&hdoc);
    current = *parsed_list;
    while (current)
	{
        if (current->type == COMMAND)
		{
            i = 0;
            while (current->command[i] != NULL)
                i++;
            char **new_command;
            allocate_new_command(&new_command, current->command, i);
            free(current->command);
            current->command = new_command;
            current->command[i] = hdoc->cmd;
            current->command[i + 1] = NULL;
            break;
        }
        current = current->next;
    }
}

// void	update_command_list_with_temp_fd(t_token **parsed_list, t_hdoc *hdoc)
// {
// 	char	**new_command;
// 	t_token	*current;
// 	int		i;
// 	int		j;

// 	reset_file_pointer(&hdoc->temp_fd, ".heredoc_tmp");
// 	read_fd_to_string(&hdoc);
// 	current = *parsed_list;
// 	while (current)
// 	{
// 		if (current->type == COMMAND)
// 		{
// 			i = 0;
// 			while (current->command[i] != NULL)
// 				i++;
// 			new_command = malloc(sizeof(char *) * (i + 2));
// 			if (!new_command)
// 			{
// 				perror("Error allocating memory");
// 				exit(EXIT_FAILURE);
// 			}
// 			j = 0;
// 			while (j < i)
// 			{
// 				new_command[j] = current->command[j];
// 				j++;
// 			}
// 			free(current->command);
// 			current->command = new_command;
// 			current->command[i] = hdoc->cmd;
// 			current->command[i + 1] = NULL;
// 			break ;
// 		}
// 		current = current->next;
// 	}
// }

void	m_heredoc(t_token **parsed_list, t_mini mini)
{
	t_hdoc	*hdoc;

	hdoc = mini.hdoc;
	hdoc->parsed_list = *parsed_list;
	hdoc->env_list = mini.env_list;
	hdoc->i = 0;
	hdoc->delimiter = m_get_delimiter_lexeme(*parsed_list);
	if (!hdoc->delimiter)
	{
		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
		return ;
	}
	hdoc->temp_fd = create_temp_file();
	if (hdoc->temp_fd == -1)
		return ;
	aux_heredoc(hdoc);
	update_command_list_with_temp_fd(parsed_list, hdoc); // fix

	// reset_file_pointer(&hdoc->temp_fd, ".heredoc_tmp");
	// read_fd_to_string(&hdoc);
	close(hdoc->temp_fd);
	// ft_printf("heredoc: cmd = %s\n", hdoc->cmd); // ---debug
	// free(hdoc->cmd); // ---debug
	if (hdoc->i == 0)
		ft_printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s'\n", hdoc->delimiter);
	unlink(".heredoc_tmp");
	ft_printf("heredoc: exec?\n"); // ---debug
}

// void	m_heredoc(t_token **parsed_list)
// {
// 	char	*delimiter;
// 	int		temp_fd;
// 	int		i;

// 	i = 0;
// 	delimiter = m_get_delimiter_lexeme(*parsed_list);
// 	if (!delimiter)
// 	{
// 		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
// 		return ;
// 	}
// 	temp_fd = create_temp_file();
// 	if (temp_fd == -1)
// 		return ;
// 	aux_heredoc(delimiter, temp_fd, &i, *parsed_list);
// 	close(temp_fd);
// 	if (i == 0)
// 		ft_printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s'\n", delimiter);
// 	unlink(".heredoc_tmp");
// 	ft_printf("heredoc: exec?\n"); // ---debug
// }
