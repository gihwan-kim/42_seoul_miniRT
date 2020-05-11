/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:46:11 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:36:28 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	char			*result;
	char			*source;
	unsigned char	new_c;
	unsigned int	i;

	result = (char*)dst;
	source = (char*)src;
	new_c = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		result[i] = source[i];
		if ((unsigned char)source[i] == new_c)
			return (void*)(result + i + 1);
		i++;
	}
	result = NULL;
	return (result);
}
