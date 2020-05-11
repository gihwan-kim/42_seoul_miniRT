/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 17:27:43 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:32:02 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t d_i;
	size_t s_i;
	size_t dst_len;

	dst_len = ft_strlen(dst);
	if (!size || size <= dst_len)
		return (size + ft_strlen(src));
	else
	{
		d_i = dst_len;
		s_i = 0;
		while (src[s_i] && s_i < size - dst_len - 1)
			dst[d_i++] = src[s_i++];
		if (d_i != size)
			dst[d_i] = '\0';
		return (dst_len + ft_strlen(src));
	}
}
