/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:45:43 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:32:35 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*result;
	const char	*source;
	int			i;

	i = 0;
	result = (char*)dst;
	source = (const char*)src;
	if ((!dst && !src) || !len)
		return (dst);
	while (len--)
	{
		*(result + i) = *(source + i);
		i++;
	}
	return (dst);
}
