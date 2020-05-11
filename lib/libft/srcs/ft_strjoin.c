/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:59:50 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:32:04 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_result;
	size_t	j_r_len;
	size_t	lcat_result;

	j_r_len = ft_strlen(s1) + ft_strlen(s2);
	if (!(join_result = (char*)malloc(sizeof(char) * (j_r_len + 1))))
		return (join_result);
	ft_memset(join_result, 0, j_r_len + 1);
	ft_strlcat(join_result, s1, ft_strlen(s1) + 1);
	ft_strlcat(join_result, s2, j_r_len + 1);
	lcat_result = ft_strlen(join_result);
	if (lcat_result == j_r_len)
		return (join_result);
	else
	{
		join_result = NULL;
		return (join_result);
	}
}
