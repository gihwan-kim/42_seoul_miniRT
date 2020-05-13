/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 10:45:55 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/15 17:36:06 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t i;
	size_t src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (n)
	{
		while (src[i] && i + 1 < n)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

char	*ft_strdup(const char *str)
{
	char	*new_str;
	size_t	new_str_len;
	size_t	check;

	new_str_len = sizeof(char) * (ft_strlen(str) + 1);
	if (!(new_str = (char *)malloc(new_str_len)))
		return (new_str);
	check = ft_strlcpy(new_str, str, new_str_len) + 1;
	if (check == new_str_len)
		return (new_str);
	else
	{
		new_str = 0;
		return (new_str);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	size_t	str_len;

	str_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (s1 == 0 || s2 == 0)
		return (0);
	if (!(str = (char *)malloc(sizeof(char) * (str_len))))
		return (0);
	i = -1;
	while (*s1)
		str[++i] = *s1++;
	while (*s2)
		str[++i] = *s2++;
	str[++i] = '\0';
	return (str);
}
