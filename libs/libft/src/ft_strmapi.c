/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:00:17 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/02 19:33:56 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = ft_strdup(s);
	if (!result)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		result[i] = f(i, result[i]);
		i++;
	}
	return (result);
}
