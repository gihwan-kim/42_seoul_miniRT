/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 13:04:48 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:32:14 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_idx_of_word(char const *s, const char c, int s_idx, int check)
{
	char *c_str;

	if (!(c_str = (char*)ft_calloc(2, sizeof(char))))
		return (s_idx);
	*c_str = c;
	s_idx++;
	while (s[s_idx])
	{
		if (check)
		{
			if (!ft_strchr(c_str, s[s_idx]))
				break ;
		}
		else
		{
			if (ft_strchr(c_str, s[s_idx]))
				break ;
		}
		s_idx++;
	}
	free(c_str);
	return (s_idx);
}

static int	set_word(int *s_w_idx, int *e_w_idx, char const *s, char c)
{
	*s_w_idx = set_idx_of_word(s, c, *s_w_idx - 1, 1);
	if ((unsigned int)*s_w_idx >= ft_strlen(s))
		return (0);
	*e_w_idx = set_idx_of_word(s, c, *s_w_idx, 0);
	return (1);
}

static int	set_word_no(char const *s, char c)
{
	int s_w_idx;
	int e_w_idx;
	int word_no;

	s_w_idx = 0;
	word_no = 0;
	while (1)
	{
		if (!set_word(&s_w_idx, &e_w_idx, s, c))
			break ;
		word_no++;
		s_w_idx = e_w_idx + 1;
	}
	return (word_no);
}

char		**ft_split(char const *s, char c)
{
	int				s_w_idx;
	int				e_w_idx;
	unsigned int	word_no;
	char			**split_result;
	char			*word_ptr;

	word_no = set_word_no(s, c);
	if (!(split_result = (char**)ft_calloc(word_no + 1, (sizeof(char*)))))
		return (split_result);
	s_w_idx = 0;
	word_no = 0;
	while (1)
	{
		if (!set_word(&s_w_idx, &e_w_idx, s, c))
			break ;
		if (!(word_ptr = (char*)malloc(sizeof(char) * (e_w_idx - s_w_idx + 1))))
			return (NULL);
		ft_strlcpy(word_ptr, s + s_w_idx, e_w_idx - s_w_idx + 1);
		if (!set_word(&s_w_idx, &e_w_idx, s, c))
			break ;
		split_result[word_no++] = word_ptr;
		s_w_idx = e_w_idx + 1;
	}
	return (split_result);
}
