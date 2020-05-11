/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 17:41:34 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:32:52 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char *str;
	unsigned char check_c;

	check_c = (unsigned char)c;
	str = (unsigned char *)b;
	while (len--)
	{
		if (*(str) == check_c)
			return (str);
		str++;
	}
	str = NULL;
	return (str);
}
