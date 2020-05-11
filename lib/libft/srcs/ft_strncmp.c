/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 14:54:33 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:31:49 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	size_t	loop_i;

	loop_i = 0;
	while (loop_i < len && (s1[loop_i] || s2[loop_i]))
	{
		if (s1[loop_i] != s2[loop_i])
			return ((unsigned char)s1[loop_i] - (unsigned char)s2[loop_i]);
		loop_i++;
	}
	return (0);
}
