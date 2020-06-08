/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 19:06:14 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/09 07:48:19 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

/*
** check_three_arg
** 		check argument number is 3
** 		check split[i] is int or double
*/

int	check_three_arg(const char *str, int (*check_arg_type)(const char*))
{
	char 	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	if ((get_argument_count(split) != 3) || !split)
		return (ERROR);
	while (i < 3)
	{
		if(!check_arg_type(split[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

/*
** store_rgb
** 		after check_three_arg() function check string.
** 		call this function.
** 		if check_rgb() is false program is terminated.
*/

void	store_rgb(const char *str, t_rgb_f *rgb_ptr, t_rt *rt_info)
{
	int		color;
	char 	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	color = ft_atoi(split[0]);
	if (check_rgb(color, rt_info))
		rgb_ptr->r_ = (double)color / (double)256;
	color = ft_atoi(split[1]);
	if (check_rgb(color, rt_info))
		rgb_ptr->g_ = (double)color / (double)256;
	color = ft_atoi(split[2]);
	if (check_rgb(color, rt_info))
		rgb_ptr->b_ = (double)color / (double)256;
}

/*
** store_vec()
** 		this function must be call after call check_three_arg()
*/
void	store_vec(const char *str, t_vec *vec_ptr)
{
	char 	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	vec_ptr->x_ = ft_atof(split[0]);
	vec_ptr->y_ = ft_atof(split[1]);
	vec_ptr->z_ = ft_atof(split[2]);	
}

int	get_all_object_count(t_rt *rt_info)
{
	int	result;
	
	result = rt_info->count_->sp_ + rt_info->count_->pl_
			+ rt_info->count_->sq_ + rt_info->count_->cy_
			+ rt_info->count_->tr_;
	return (result);
}