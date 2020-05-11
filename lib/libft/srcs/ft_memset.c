/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 14:40:14 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:32:29 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*result;
	int				i;

	i = -1;
	result = dest;
	if (!len)
		return (dest);
	while (len--)
		*(result + (++i)) = (unsigned char)c;
	return (dest);
}
