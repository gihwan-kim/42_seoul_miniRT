/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 17:30:42 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/10 10:32:20 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	sub_str_len;

	sub_str = NULL;
	// if ((ft_strlen(s) - start) < len)
	// 	return (sub_str);
	if (ft_strlen(s) < start)
		return (sub_str);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (!(sub_str = (char*)malloc(sizeof(char) * (len + 1))))
		return (sub_str);
    *(sub_str + len) = 0;
	ft_strlcpy(sub_str, (s + start), len + 1);
	sub_str_len = ft_strlen(sub_str);
	if (sub_str_len == len)
		return (sub_str);
	else
	{
		free(sub_str);
		sub_str = NULL;
		return (sub_str);
	}
}
