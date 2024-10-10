/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:31 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/10 16:23:50 by lsampiet         ###   ########.fr       */
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

typedef struct s_mini t_mini;

struct s_mini
{
	char	*input;
};

// Lexical Analysis Functions
// int		m_check_closing_quote(char *line, char specific, int i);
int	m_check_quotes(const char *line);
void	lexical_analysis(char *line);

// Pipes and child processes creation functions


// Paths to commands generation functions


// Memory cleansing and error functions

#endif