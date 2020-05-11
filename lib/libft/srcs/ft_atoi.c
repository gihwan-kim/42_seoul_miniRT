/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 17:33:18 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:34:33 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char *str)
{
	int s_i;

	s_i = 0;
	while ((str[s_i] >= 9 && str[s_i] <= 13) || str[s_i] == 32)
		s_i++;
	return (s_i);
}

static int	ft_power(int nb, int power)
{
	if (!power)
		return (1);
	else
	{
		nb = nb * ft_power(nb, power - 1);
		return (nb);
	}
}

static int	ft_getnbr(int s_idx, int e_idx, const char *nptr)
{
	int result;

	result = 0;
	while (s_idx < e_idx)
	{
		result = result + (nptr[s_idx] - '0') * ft_power(10, e_idx - s_idx - 1);
		s_idx++;
	}
	return (result);
}

int			ft_atoi(const char *nptr)
{
	int s_idx;
	int e_idx;
	int sign;

	sign = 1;
	s_idx = 0;
	if (*nptr)
	{
		s_idx = ft_isspace(nptr);
		if (nptr[s_idx] == '-' || nptr[s_idx] == '+')
		{
			if (nptr[s_idx] == '-')
				sign *= -1;
			s_idx++;
		}
		e_idx = s_idx;
		while (nptr[e_idx] >= 48 && nptr[e_idx] <= 57)
			e_idx++;
		if (e_idx == s_idx)
			return (0);
		return (sign * ft_getnbr(s_idx, e_idx, nptr));
	}
	else
		return (0);
}
