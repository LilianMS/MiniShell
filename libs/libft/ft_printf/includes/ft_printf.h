/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:34:19 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/03 12:22:52 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../includes/libft.h"

int	ft_print_char(int c);
int	ft_print_str(char *str);
int	ft_print_nbr(long int nbr, int base, int upper);
int	ft_print_pnbr(unsigned long nbr, int base, int upper);
int	ft_print_pointer(unsigned long p);
int	ft_check(va_list ap, char c);
int	ft_mod(char c);
int	ft_wth_mod(va_list ap, char s1, char s2);
int	ft_mod_has(va_list ap, char s2);
int	ft_mod_spc(va_list ap, char s2);
int	ft_mod_plus(va_list ap, char s2);
int	ft_printf(const char *s, ...);

#endif
