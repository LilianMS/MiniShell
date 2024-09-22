/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:01:31 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/03 16:00:31 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	pid_t	pid_1;
	pid_t	pid_2;
	char	**path_envp;
	int		status;
	int		access_code;
}			t_pipex;

void	px_execve(t_pipex *p, char *cmd);
void	px_error(char *str);
int		px_get_status(int exit_status);
void	ft_free_split(char **split);
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3);
char	*ft_getenv(t_pipex *p, char *name);

#endif