/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:16:57 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/16 16:06:23 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;

	dst = malloc(ft_strlen (s) + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s, ft_strlen (s) + 1);
	return (dst);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(s);
	if (len > n)
		len = n;
	dst = malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s, len + 1);
	return (dst);
}
