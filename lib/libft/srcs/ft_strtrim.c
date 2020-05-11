/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 17:57:18 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:31:39 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_idx(const char *str, const char *set, int str_idx, int check)
{
	while (1)
	{
		if (check)
		{
			if (!ft_strchr(set, str[++str_idx]))
				return (str_idx);
		}
		else
		{
			if (!ft_strchr(set, str[--str_idx]))
				return (str_idx + 1);
		}
	}
}

char		*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	s_idx;
	unsigned int	e_idx;
	unsigned int	t_r_len;
	char			*trim_result;

	trim_result = NULL;
	s_idx = set_idx(s1, set, -1, 1);
	e_idx = set_idx(s1, set, ft_strlen(s1), 0);
	t_r_len = e_idx - s_idx + 1;
	if (!(trim_result = (char*)malloc(sizeof(char) * (t_r_len))))
		return (trim_result);
	ft_strlcpy(trim_result, s1 + s_idx, t_r_len);
	if (ft_strlen(trim_result) == t_r_len - 1)
		return (trim_result);
	else
	{
		*trim_result = 0;
		return (trim_result);
	}
}
