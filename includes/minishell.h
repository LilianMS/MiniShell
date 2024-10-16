/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:31 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/15 20:33:51 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/includes/libft.h"
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_mini	t_mini;

struct s_mini
{
	char	*input;
};

// Lexical Analysis Functions
int		m_check_quotes(const char *line);
void	m_lexical_analysis(char *line);

// Parsing Functions

#endif