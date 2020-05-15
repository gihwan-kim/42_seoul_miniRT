/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 10:41:19 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/15 14:14:23 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing_resolution(char **split, t_rt *rt_info)
{
	t_r *resolution;

	if (!(resolution = malloc(sizeof(t_r))))
		return (print_error("Out of memmory!\n"));
	if (get_argument_count(split)!= 3)
		return (print_error("The number of argument is wrong!\n"));
		
	if (check_str_isdigit(split[1]))
		resolution->size_x_ = ft_atoi(split[1]);
	else
		return (print_error("Argument of resolution is not integer!\n"));
	if (check_str_isdigit(split[2]))
		resolution->size_y_ = ft_atoi(split[2]);
	else
		return (print_error("Argument of resolution is not integer!\n"));
	rt_info->count_->r_ += 1;
	if (rt_info->count_->r_ >= 2)
		return (print_error("Count of resolution must be 1!\n"));
	rt_info->t_r_ = resolution;
	return (SUCCESS);
}

int	parsing_ambient(char **split, t_rt *rt_info)
{
	t_a *ambient;

	if (!(ambient = malloc(sizeof(t_a))))
		return (print_error("Out of memmory!\n"));
	if (get_argument_count(split) != 3)
		return (print_error("The number of argument is wrong!\n"));
	if (check_str_isdouble(split[1]))
		ambient->light_ = ft_atof(split[1]);
	else
		return (print_error("Argument of ambient is not double!\n"));
	if (check_three_arg(split[2], check_str_isdigit))
		store_rgb(split[2], &(ambient->rgb_));
	else
		return (print_error("Argument of ambient is not integer!\n"));
	rt_info->count_->a_ += 1;
	if (rt_info->count_->a_ >= 2)
		return (print_error("Count of ambient must be 1!\n"));
	rt_info->t_a_ = ambient;
	return (SUCCESS);
}

int	parsing_camera(char **split, t_rt *rt_info)
{
	t_c *camera;

	if (!(camera = malloc(sizeof(t_a))))
		return (print_error("Out of memmory!\n"));
	if (get_argument_count(split) != 4)
		return (print_error("The number of argument is wrong!\n"));
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(camera->vec_));
	else
		return (print_error("Argument of camera is not doulbe!\n"));
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(camera->normal_vec_));
	else
		return (print_error("Argument of camera is not integer!\n"));
	if (check_str_isdigit(split[3]))
		camera->fov_ = ft_atoi(split[3]);
	else
		return (print_error("Argument of resolution is not integer!\n"));
	rt_info->count_->c_ += 1;
	ft_lstadd_back(&(rt_info->lst_c_),ft_lstnew(camera));
	return (SUCCESS);
}

int	parsing_light(char **split, t_rt *rt_info)
{
	t_l *light;

	if (!(light = malloc(sizeof(t_a))))
		return (print_error("Out of memmory!\n"));
	if (get_argument_count(split) != 4)
		return (print_error("The number of argument is wrong!\n"));
	// view point xyz
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(light->vec_));
	else
		return (print_error("Argument of light is not doulbe!\n"));
	// ratio
	if (check_str_isdouble(split[2]))
		light->light_ = ft_atof(split[2]);
	else
		return (print_error("Argument of light is not integer!\n"));
	// rgb
	if (check_three_arg(split[3], check_str_isdigit))
		store_rgb(split[3], &(light->rgb_));
	else
		return (print_error("Argument of light is not integer!\n"));
	rt_info->count_->l_ += 1;
	ft_lstadd_back(&(rt_info->lst_l_),ft_lstnew(light));
	return (SUCCESS);
}
