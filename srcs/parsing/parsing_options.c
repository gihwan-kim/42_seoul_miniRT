/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 10:41:19 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 21:23:10 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing_resolution(char **split, t_rt *rt_info)
{
	t_r *resolution;

	if (!(resolution = malloc(sizeof(t_r))))
		return (print_error_comment("Out of memmory!", rt_info));
	if (get_argument_count(split) != 3)
		return (print_error(22, "The number of argument is wrong!", rt_info));
	if (check_str_isdigit(split[1]))
		resolution->size_x_ = ft_atoi(split[1]);
	else
		return (print_error(22, "Resolution is not integer!", rt_info));
	if (check_str_isdigit(split[2]))
		resolution->size_y_ = ft_atoi(split[2]);
	else
		return (print_error(22, "Resolution is not integer!", rt_info));
	if (resolution->size_x_ <= 0 && resolution->size_y_ <= 0)
		return (print_error(22, "Resolution is positive!", rt_info));
	rt_info->count_->r_ += 1;
	if (rt_info->count_->r_ >= 2)
		return (print_error(22, "Count of resolution must be 1!", rt_info));
	rt_info->t_r_ = resolution;
	return (SUCCESS);
}

int	parsing_ambient(char **split, t_rt *rt_info)
{
	t_a *ambient;

	if (!(ambient = malloc(sizeof(t_a))))
		return (print_error_comment("Out of memmory!", rt_info));
	if (get_argument_count(split) != 3)
		return (print_error(22, "The number of argument is wrong!", rt_info));
	if (check_str_isdouble(split[1]))
		ambient->light_ = check_light(ft_atof(split[1]), rt_info);
	else
		return (print_error(22, "not double!", rt_info));
	if (check_three_arg(split[2], check_str_isdigit))
		store_rgb(split[2], &(ambient->rgb_), rt_info);
	else
		return (print_error(22, "not integer!", rt_info));
	rt_info->count_->a_ += 1;
	if (rt_info->count_->a_ >= 2)
		return (print_error(22, "Count of ambient must be 1!", rt_info));
	rt_info->t_a_ = ambient;
	return (SUCCESS);
}

int	parsing_camera(char **split, t_rt *rt_info)
{
	t_c *camera;

	if (!(camera = malloc(sizeof(t_a))))
		return (print_error_comment("Out of memmory!", rt_info));
	if (get_argument_count(split) != 4)
		return (print_error(22, "The number of argument is wrong!", rt_info));
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(camera->vec_));
	else
		return (print_error(22, "Camera point is not doulbe!", rt_info));
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(camera->orient_vec_));
	else
		return (print_error(22, "Camera point is not integer!", rt_info));
	if (check_str_isdigit(split[3]))
		camera->fov_ = ft_atoi(split[3]);
	else
		return (print_error(22, "Fov is not integer!", rt_info));
	if (0 > camera->fov_ || camera->fov_ > 180)
		return (print_error(22, "Fov range is [0,180]!", rt_info));
	rt_info->count_->c_ += 1;
	ft_lstadd_back(&(rt_info->lst_c_), ft_lstnew(camera));
	return (SUCCESS);
}

int	parsing_light(char **split, t_rt *rt_info)
{
	t_l *light;

	if (!(light = malloc(sizeof(t_a))))
		return (print_error_comment("Out of memmory!", rt_info));
	if (get_argument_count(split) != 4)
		return (print_error(22, "The number of argument is wrong!", rt_info));
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(light->vec_));
	else
		return (print_error(22, "Light point is not doulbe!", rt_info));
	if (check_str_isdouble(split[2]))
		light->light_ = check_light(ft_atof(split[2]), rt_info);
	else
		return (print_error(22, "Light ratio is not double!", rt_info));
	if (check_three_arg(split[3], check_str_isdigit))
		store_rgb(split[3], &(light->rgb_), rt_info);
	else
		return (print_error(22, "Light rgb is not integer!", rt_info));
	ft_lstadd_back(&(rt_info->lst_l_), ft_lstnew(light));
	rt_info->count_->l_ += 1;
	return (SUCCESS);
}

int	set_cylinder(char **split, t_cy *cylinder, t_rt *rt_info)
{
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(cylinder->vec_));
	else
		return (print_error(22, "not doulbe!", rt_info));
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(cylinder->orient_vec_));
	else
		return (print_error(22, "not integer!", rt_info));
	if (check_str_isdouble(split[3]))
		cylinder->diameter_ = check_size(ft_atof(split[3]), rt_info);
	else
		return (print_error(22, "not integer!", rt_info));
	if (check_str_isdouble(split[4]))
		cylinder->height_ = check_size(ft_atof(split[4]), rt_info);
	else
		return (print_error(22, "not integer!", rt_info));
	if (check_three_arg(split[5], check_str_isdigit))
		store_rgb(split[5], &(cylinder->rgb_), rt_info);
	else
		return (print_error(22, "Arg of cylinder is not integer!", rt_info));
	return (SUCCESS);
}
