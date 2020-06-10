/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 10:53:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 20:08:54 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t			get_argument_count(char **split)
{
	size_t count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

int				check_str_isdigit(const char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (ERROR);
		str++;
	}
	return (SUCCESS);
}

/*
** check str is number.number or number
*/

int				check_str_isdouble(const char *str)
{
	char	**split;
	int		i;

	i = 0;
	if (!(split = ft_split(str, '.')))
		return (ERROR);
	if (get_argument_count(split) == 1)
	{
		if (!check_str_isdigit(str))
			return (ERROR);
		return (SUCCESS);
	}
	while (split[i])
		i++;
	if (i >= 3)
		return (ERROR);
	if (split[0][0] == '-')
	{
		if (!check_str_isdigit(split[0] + 1))
			return (ERROR);
	}
	else
	{
		if (!(check_str_isdigit(split[0])))
			return (ERROR);
	}
	if (!(check_str_isdigit(split[1])))
		return (ERROR);
	return (SUCCESS);
}

static double	itof_under_decimal_point(size_t n, unsigned int integer)
{
	unsigned int	nbr;
	double			result;

	nbr = 10;
	if (!n)
		return (0.0);
	while (--n)
		nbr *= 10;
	result = (double)integer / (double)nbr;
	return (result);
}

/*
** Call ft_atof after check str formula is single "number.number"
** not "number.number number.number"
*/

double			ft_atof(const char *str)
{
	double	result;
	char	**split;
	size_t	split_count;
	double	sign;

	split = ft_split(str, '.');
	split_count = get_argument_count(split);
	sign = 1.0;
	if (split_count == 1)
	{
		result = (double)ft_atoi(str);
		return (result);
	}
	if (split[0][0] == '-')
	{
		sign = -1.0;
		result = (double)ft_atoi(split[0] + 1);
	}
	else
		result = (double)ft_atoi(split[0]);
	if (split_count == 2)
		result += itof_under_decimal_point(ft_strlen(split[1]),
											ft_atoi(split[1]));
	result *= sign;
	return (result);
}
