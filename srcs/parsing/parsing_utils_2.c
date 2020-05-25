/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 19:06:14 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/24 10:30:52 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

// arg 가 3개인지 get_argument_count() 로 확인
// int 또는 double 인지 check_arg_type() 로 확인
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

// check_three_arg 함수로 문자열을 확인한후 함수를 호출할 것!
void	store_rgb(const char *str, t_rgb *rgb_ptr)
{
	char 	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	rgb_ptr->r_ = ft_atoi(split[0]);
	rgb_ptr->g_ = ft_atoi(split[1]);
	rgb_ptr->b_ = ft_atoi(split[2]);
}

// check_three_arg 함수로 문자열을 확인한후 함수를 호출할 것!
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