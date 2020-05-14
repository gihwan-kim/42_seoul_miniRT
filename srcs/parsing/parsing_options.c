/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 10:41:19 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/14 17:23:08 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_r	*parsing_resolution(char **split, t_rt *rt_info)
{
	t_r *resolution;

	if (!(resolution = malloc(sizeof(t_r))))
		return (print_error_ptr("Out of memmory!\n"));
	if (get_argument_count(split)!= 2)
		return (print_error_ptr("The number of argument is wrong!\n"));
	if (check_str_isdigit(split[1]))
		resolution->size_x = ft_atoi(split[1]);
	else
		return (print_error_ptr("Argument of resolution is not integer!\n"));
	if (check_str_isdigit(split[2]))
		resolution->size_y = ft_atoi(split[2]);
	else
		return (print_error_ptr("Argument of resolution is not integer!\n"));
	rt_info->count_->r_ += 1;
	if (rt_info->count_->r_ >= 2)
		return (print_error_ptr("Count of resolution must be 1!\n"));
	return (resolution);
}

t_a *parsing_ambient(char **split, t_rt *rt_info)
{
	t_a *ambient;

	if (!(ambient = malloc(sizeof(t_r))))
		return (print_error_ptr("Out of memmory!\n"));
	if (get_argument_count(split) != 2)
		return (print_error_ptr("The number of argument is wrong!\n"));
	
	return (ambient);
}