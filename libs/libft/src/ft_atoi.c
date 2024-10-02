/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:44:41 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/02 19:31:31 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	res;

	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	res = 0;
	while (ft_isdigit(nptr[i]))
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
