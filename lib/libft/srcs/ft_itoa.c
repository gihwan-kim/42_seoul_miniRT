/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 15:38:35 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:33:30 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_itoa()
**	n : the integer to convert
** 	return value : integer -> string, fail -> NULL
**
** make_str()
** 	make dynamic str array
**
** set_str()
**	calculate str length
** 	check sign(- or +)
** 	fill str
*/

static char	*make_str(int *str_len, int sign, char *str)
{
	if (sign)
	{
		if (!(str = (char*)malloc(sizeof(char) * (++*str_len + 1))))
			return (str);
	}
	else
	{
		if (!(str = (char*)malloc(sizeof(char) * (*str_len + 1))))
			return (str);
	}
	return (str);
}

static char	*set_str(unsigned int n, int sign)
{
	int				str_len;
	int				i;
	unsigned int	temp;
	char			*str;

	temp = n;
	i = -1;
	str_len = 1;
	str = NULL;
	while (temp /= 10)
		str_len++;
	if (!(str = make_str(&str_len, sign, str)))
		return (str);
	while (++i < str_len)
	{
		str[str_len - i - 1] = '0' + n % 10;
		if (sign && !(str_len - i - 1))
			str[str_len - i - 1] = '-';
		n = n / 10;
	}
	str[str_len] = '\0';
	return (str);
}

char		*ft_itoa(int n)
{
	unsigned int temp;

	temp = 0;
	if (n >= 0)
		return (set_str(n, 0));
	else
	{
		temp = n * -1;
		return (set_str(temp, 1));
	}
}
