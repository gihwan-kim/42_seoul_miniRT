/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 10:41:21 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/09 08:48:58 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
** identifier: sp
** x,y,z coordinates of the sphere center
** the sphere diameter
** R,G,B colors in range [0-256]
*/

int	parsing_sphere(char **split, t_rt *rt_info)
{
	t_sp *sphere;
	
	if (!(sphere = malloc(sizeof(t_a))))
		return (print_error_comment("Out of memmory!", rt_info));
	if (get_argument_count(split) != 4)
		return (print_error(22, "The number of argument is wrong!", rt_info));
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(sphere->vec_));
	else
		return (print_error(22, "not doulbe!", rt_info));
	if (check_str_isdouble(split[2]))
		sphere->diameter_ = check_size(ft_atof(split[2]) / 2, rt_info);
	else
		return (print_error(22, "not integer!", rt_info));
	if (check_three_arg(split[3], check_str_isdigit))
		store_rgb(split[3], &(sphere->rgb_), rt_info);
	else
		return (print_error(22, "not integer!", rt_info));
	rt_info->count_->sp_ += 1;
	ft_lstadd_back(&(rt_info->lst_sp_),ft_lstnew(sphere));
	return (SUCCESS);
}

/*
** identifier: pl
** x,y,z coordinates
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
** R,G,B colors in range [0-256]
*/

int	parsing_plane(char **split, t_rt *rt_info)
{
	t_pl *plane;

	if (!(plane = malloc(sizeof(t_a))))
		return (print_error_comment("Out of memmory!", rt_info));
	if (get_argument_count(split) != 4)
		return (print_error(22, "The number of argument is wrong!", rt_info));
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(plane->vec_));
	else
		return (print_error(22, "not double!", rt_info));
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(plane->orient_vec_));
	else
		return (print_error(22, "not integer!", rt_info));
	if (check_three_arg(split[3], check_str_isdigit))
		store_rgb(split[3], &(plane->rgb_), rt_info);
	else
		return (print_error(22, "not integer!", rt_info));
	rt_info->count_->pl_ += 1;
	ft_lstadd_back(&(rt_info->lst_pl_),ft_lstnew(plane));
	return (SUCCESS);
}

/*
** identifier: sq
** x,y,z coordinates of the square center
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
** side size
** R,G,B colors in range [0-256]
*/

int	parsing_square(char **split, t_rt *rt_info)
{
	t_sq *square;

	if (!(square = malloc(sizeof(t_a))))
		return (print_error_comment("Out of memmory!", rt_info));
	if (get_argument_count(split) != 5)
		return (print_error(22, "The number of argument is wrong!", rt_info));
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(square->vec_));
	else
		return (print_error(22, "not doulbe!", rt_info));
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(square->orient_vec_));
	else
		return (print_error(22, "not integer!", rt_info));
	if (check_str_isdouble(split[3]))
		square->side_size = check_size(ft_atof(split[3]), rt_info);
	else
		return (print_error(22, "not integer!", rt_info));
	if (check_three_arg(split[4], check_str_isdigit))
		store_rgb(split[4], &(square->rgb_), rt_info);
	else
		return (print_error(22, "not integer!", rt_info));
	rt_info->count_->sq_ += 1;
	ft_lstadd_back(&(rt_info->lst_sq_),ft_lstnew(square));
	return (SUCCESS);
}

/*
** identifier: cy
** x,y,z coordinates
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
** the cylinder diameter
** the cylinder height
** R,G,B colors in range [0,256]
*/

int	parsing_cylinder(char **split, t_rt *rt_info)
{
	t_cy *cylinder;

	if (!(cylinder = malloc(sizeof(t_a))))
		return (print_error_comment("Out of memmory!", rt_info));
	if (get_argument_count(split) != 6)
		return (print_error(22, "The number of argument is wrong!", rt_info));
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
		return (print_error(22, "Argument of cylinder is not integer!", rt_info));
	rt_info->count_->cy_ += 1;
	ft_lstadd_back(&(rt_info->lst_cy_), ft_lstnew(cylinder));
	return (SUCCESS);
}

/*
** identifier: tr
** x,y,z coordinates of the first point
** x,y,z coordinates of the second point
** x,y,z coordinates of the third point
** R,G,B colors in range [0,256]
*/

int	parsing_triangle(char **split, t_rt *rt_info)
{
	t_tr *triangle;

	if (!(triangle = malloc(sizeof(t_a))))
		return (print_error_comment("Out of memmory!", rt_info));
	if (get_argument_count(split) != 5)
		return (print_error(22, "The number of argument is wrong!", rt_info));
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(triangle->vec_1_));
	else
		return (print_error(22, "not doulbe!", rt_info));
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(triangle->vec_2_));
	else
		return (print_error(22, "not doulbe!", rt_info));
	if (check_three_arg(split[3], check_str_isdouble))
		store_vec(split[3], &(triangle->vec_3_));
	else
		return (print_error(22, "not doulbe!", rt_info));
	if (check_three_arg(split[4], check_str_isdigit))
		store_rgb(split[4], &(triangle->rgb_), rt_info);
	else
		return (print_error(22, "not integer!", rt_info));
	rt_info->count_->tr_ += 1;
	ft_lstadd_back(&(rt_info->lst_tr_),ft_lstnew(triangle));
	return (SUCCESS);
}