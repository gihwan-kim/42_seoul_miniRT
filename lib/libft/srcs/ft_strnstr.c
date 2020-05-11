/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:12:36 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:31:46 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t b_i;
	size_t l_i;

	b_i = 0;
	if (!little[b_i] || (big == little))
		return ((char*)big);
	while (big[b_i] && b_i < len)
	{
		l_i = 0;
		while ((big[b_i + l_i] == little[l_i]) && ((b_i + l_i) < len))
			l_i++;
		if (l_i == ft_strlen(little))
			return ((char*)(big + b_i));
		b_i++;
	}
	return (NULL);
}
