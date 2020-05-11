/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:03:46 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:32:07 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*new_str;
	size_t	new_str_len;
	size_t	check;

	new_str_len = sizeof(char) * (ft_strlen(str) + 1);
	if (!(new_str = (char*)malloc(new_str_len)))
		return (new_str);
	check = ft_strlcpy(new_str, str, new_str_len) + 1;
	if (check == new_str_len)
		return (new_str);
	else
	{
		new_str = NULL;
		return (new_str);
	}
}
