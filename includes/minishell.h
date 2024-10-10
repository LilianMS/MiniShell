/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:31 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/10 12:46:15 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libs/libft/includes/libft.h"
#include "../libs/libft/ft_printf/includes/ft_printf.h"
#include "../libs/libft/gnl/includes/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_pipex t_pipex;

struct s_pipex
{
	int	fd_in;
	int	fd_out;
	int	pid[2];
	int	status;
};

//Lexical Analysis Functions
int	check_quotes(char	*line);
void	lexical_analysis(char *line);
char	*read_line(void);

// Pipes and child processes creation functions
void	execute(int argc, char **argv, char **envp);
void	child_process(char **argv, char **envp, t_pipex *data, int *fd);
void	brother_process(char **argv, char **envp, t_pipex *data, int *fd);
int	create_pipex(char **argv, char **envp, t_pipex *data);

// Paths to commands generation functions
char	*check_cmd(char **argv, char **envp);
char	*create_path(char *cmd, char **cmd_paths, char **envp);
void	check_permissions(char *cmd, char **cmd_paths);

// Memory cleansing and error functions
void	close_fds(void);
void	error(int status);
void	free_paths(char **paths);

#endif