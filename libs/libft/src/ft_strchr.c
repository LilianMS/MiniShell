/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:17:14 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/02 19:33:17 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != (unsigned char)c)
		if (!*s++)
			return (0);
	return ((char *)s);
}
