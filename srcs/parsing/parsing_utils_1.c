/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 10:53:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/15 10:13:02 by gihwan-kim       ###   ########.fr       */
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

// 문자열이 "number.number" 와같은 형태인지 확인한다.
int		check_str_isdouble(const char *str)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, '.');
	if (!split)
		return (ERROR);
	printf("split[0] : |%s|\n count : %ld\n", split[0], get_argument_count(split));
	if (get_argument_count(split) == 1)
	{
		if (!check_str_isdigit(str))
			return (ERROR);
		return (SUCCESS);
	}
	while(split[i])
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
		if(!(check_str_isdigit(split[0])))
			return (ERROR);
	}
	if (!(check_str_isdigit(split[1])))
		return (ERROR);
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

// str문자열은 무조건 "numuber.number " 형태이어야한다.
// str을 넘겨주기 전에 str 이 위 형태인지 확인을 하고 함수를 호출 할것
// "111.111" -> 111.111
// "111.111, 111.1111" X
double	ft_atof(const char *str)
{
	double	result;
	char 	**split;
	size_t	split_count;
	// int		i;

	// i = 0;
	split = ft_split(str, '.');
	split_count = get_argument_count(split);
	if (split_count == 1)
		return result = (double)ft_atoi(str);
	// while (split[i])
	// 	i++;
	// if (!split || i >= 3)
	// 	return (0.0);
	// char **split;
	// int i;
	// i = 0;
	// split = ft_split(str, '.');
	// while(split[i])
	// 	i++;
	// if (!split || i >= 3)
	// 	return (0.0);
	// if (split[0][0] == '-')
	// {
	// 	if (!check_str_isdigit(split[0] + 1))
	// 		return (0.0);
	// }
	// else
	// {
	// 	if(!(check_str_isdigit(split[0])))
	// 		return (0.0);
	// }
	// if (!(check_str_isdigit(split[1])))
	// 	return (0.0);

	// integer = ft_atoi(split[1]);
	result = (double)ft_atoi(split[0]);
	// if (i == 2)
	// 	result += itof_under_decimal_point(ft_strlen(split[1]), ft_atoi(split[1]));
	
	if (split_count == 2)
		result += itof_under_decimal_point(ft_strlen(split[1]), ft_atoi(split[1]));
	return (result);
}