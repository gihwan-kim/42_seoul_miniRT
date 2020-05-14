/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 10:53:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/14 17:21:53 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 필요한 함수
** 	array to float
** 	array is int -> ft_isdigit
** 	array is float
*/

#include "parsing.h"

size_t	get_argument_count(char **split)
{
	size_t count;

	count = 0;
	while(split[count])
		count++;
	return (count);
}

int		check_str_isdigit(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (ERROR);
		str++;
	}
	return (SUCCESS);
}

static double itof_under_decimal_point(size_t n, unsigned int integer)
{
	unsigned int 	nbr;
	double			result;

	nbr = 10;
	if (!n)
		return (0.0);
	while (--n)
		nbr *= 10;
	result = (double)integer / (double)nbr;
	return (result);
}

double	ft_atof(const char *str)
{
	char **split;
	double result;
	int i;
	
	i = 0;
	split = ft_split(str, '.');
	while(split[i])
		i++;
	if (!split || i == 1)
		return (0.0);
	if (split[0][0] == '-')
	{
		if (!check_str_isdigit(split[0] + 1))
			return (0.0);
	}
	else
	{
		if(!(check_str_isdigit(split[0])))
			return (0.0);
	}
	result = (double)ft_atoi(split[0]);
	if (!(check_str_isdigit(split[1])))
		return (0.0);
	// integer = ft_atoi(split[1]);
	result += itof_under_decimal_point(ft_strlen(split[1]), ft_atoi(split[1]));
	return (result);
}