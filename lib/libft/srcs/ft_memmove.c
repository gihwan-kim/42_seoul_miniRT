/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 12:49:59 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:46:02 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*source;
	size_t	i;
	char	*dest;

	dest = (char*)dst;
	source = (char*)src;
	if (dst > src)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dest[i] = source[i];
		}
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
