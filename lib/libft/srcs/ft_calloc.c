/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:15:55 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:34:28 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void *new_memory;

	if (number == 0 || size == 0)
	{
		size = 1;
		number = 1;
	}
	if (!(new_memory = malloc(number * size)))
	{
		new_memory = NULL;
		return (new_memory);
	}
	if (new_memory)
		ft_bzero(new_memory, number * size);
	return (new_memory);
}
