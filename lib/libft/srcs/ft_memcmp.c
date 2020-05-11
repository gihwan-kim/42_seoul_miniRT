/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 17:50:56 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:32:40 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	unsigned char	*s_1;
	unsigned char	*s_2;
	int				result;
	size_t			loop_i;

	s_1 = (unsigned char*)s1;
	s_2 = (unsigned char*)s2;
	loop_i = 0;
	result = 0;
	while (loop_i < len)
	{
		result = *(s_1 + loop_i) - *(s_2 + loop_i);
		if (!result)
			loop_i++;
		else
			break ;
	}
	return (result);
}
