/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:01:17 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/16 11:37:16 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)  // Se o ponteiro original for NULL, funciona como malloc
		return (malloc(new_size));
	if (new_size == 0)  // Se o novo tamanho for 0, funciona como free
	{
		free(ptr);
		return (NULL);
	}
	// Aloca nova memória
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	// Copia o conteúdo da área antiga para a nova (tamanho original desconhecido, assumimos o novo tamanho)
	ft_memcpy(new_ptr, ptr, new_size);  // Supõe que estamos copiando até o tamanho novo
	free(ptr);  // Libera a memória antiga

	return (new_ptr);
}






/*
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	if (!ptr)  // Se o ponteiro original for NULL, funciona como malloc
		return (malloc(new_size));
	if (new_size == 0)  // Se o novo tamanho for 0, funciona como free
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)  // Verifica se a alocação falhou
		return (NULL);
	if (old_size < new_size)  // Copia o conteúdo antigo para o novo bloco
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);  // Libera a memória original
	return (new_ptr);
}
*/