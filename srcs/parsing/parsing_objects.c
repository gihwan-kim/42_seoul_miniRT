/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 10:41:21 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/15 13:47:15 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing_sphere(char **split, t_rt *rt_info)
{
	t_sp *sphere;

	if (!(sphere = malloc(sizeof(t_a))))
		return (print_error("Out of memmory!\n"));
	if (get_argument_count(split) != 3)
		return (print_error("The number of argument is wrong!\n"));
	// xyz
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(sphere->vec_));
	else
		return (print_error("Argument of sphere is not doulbe!\n"));
	// diameter
	if (check_str_isdouble(split[2]))
		sphere->diameter_ = ft_atof(split[2]);
	else
		return (print_error("Argument of sphere is not integer!\n"));
	// rgb
	if (check_three_arg(split[3], check_str_isdigit))
		store_rgb(split[3], &(sphere->rgb_));
	else
		return (print_error("Argument of sphere is not integer!\n"));
	rt_info->count_->sp_ += 1;
	ft_lstadd_back(&(rt_info->lst_sp_),ft_lstnew(sphere));
	return (SUCCESS);
}

int	parsing_plane(char **split, t_rt *rt_info)
{
	t_pl *plane;

	if (!(plane = malloc(sizeof(t_a))))
		return (print_error("Out of memmory!\n"));
	if (get_argument_count(split) != 3)
		return (print_error("The number of argument is wrong!\n"));
	// xyz
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(plane->vec_));
	else
		return (print_error("Argument of plane is not doulbe!\n"));
	// normalize vec
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(plane->normal_vec_));
	else
		return (print_error("Argument of plane is not integer!\n"));
	// rgb
	if (check_three_arg(split[3], check_str_isdigit))
		store_rgb(split[3], &(plane->rgb_));
	else
		return (print_error("Argument of plane is not integer!\n"));
	rt_info->count_->pl_ += 1;
	ft_lstadd_back(&(rt_info->lst_pl_),ft_lstnew(plane));
	return (SUCCESS);
}

int	parsing_square(char **split, t_rt *rt_info)
{
	t_sq *square;

	if (!(square = malloc(sizeof(t_a))))
		return (print_error("Out of memmory!\n"));
	if (get_argument_count(split) != 4)
		return (print_error("The number of argument is wrong!\n"));
	// xyz
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(square->vec_));
	else
		return (print_error("Argument of square is not doulbe!\n"));
	// normalize vec
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(square->normal_vec_));
	else
		return (print_error("Argument of square is not integer!\n"));
	// side size
	if (check_str_isdouble(split[3]))
		square->side_size = ft_atof(split[3]);
	else
		return (print_error("Argument of square is not integer!\n"));
	// rgb
	if (check_three_arg(split[4], check_str_isdigit))
		store_rgb(split[4], &(square->rgb_));
	else
		return (print_error("Argument of square is not integer!\n"));
	rt_info->count_->sq_ += 1;
	ft_lstadd_back(&(rt_info->lst_sq_),ft_lstnew(square));
	return (SUCCESS);
}

int	parsing_cylinder(char **split, t_rt *rt_info)
{
	t_cy *cylinder;

	if (!(cylinder = malloc(sizeof(t_a))))
		return (print_error("Out of memmory!\n"));
	if (get_argument_count(split) != 5)
		return (print_error("The number of argument is wrong!\n"));
	// xyz
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(cylinder->vec_));
	else
		return (print_error("Argument of cylinder is not doulbe!\n"));
	// normalize vec
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(cylinder->normal_vec_));
	else
		return (print_error("Argument of cylinder is not integer!\n"));
	// diameter
	if (check_str_isdouble(split[3]))
		cylinder->diameter_ = ft_atof(split[3]);
	else
		return (print_error("Argument of cylinder is not integer!\n"));
	// height
	if (check_str_isdouble(split[4]))
		cylinder->height_ = ft_atof(split[4]);
	else
		return (print_error("Argument of cylinder is not integer!\n"));
	// rgb
	if (check_three_arg(split[5], check_str_isdigit))
		store_rgb(split[5], &(cylinder->rgb_));
	else
		return (print_error("Argument of cylinder is not integer!\n"));
	rt_info->count_->cy_ += 1;
	ft_lstadd_back(&(rt_info->lst_cy_),ft_lstnew(cylinder));
	return (SUCCESS);
}

int	parsing_triangle(char **split, t_rt *rt_info)
{
	t_sq *triangle;

	if (!(triangle = malloc(sizeof(t_a))))
		return (print_error("Out of memmory!\n"));
	if (get_argument_count(split) != 4)
		return (print_error("The number of argument is wrong!\n"));
	// xyz
	if (check_three_arg(split[1], check_str_isdouble))
		store_vec(split[1], &(triangle->vec_));
	else
		return (print_error("Argument of triangle is not doulbe!\n"));
	// normalize vec
	if (check_three_arg(split[2], check_str_isdouble))
		store_vec(split[2], &(triangle->normal_vec_));
	else
		return (print_error("Argument of triangle is not integer!\n"));
	// side size
	if (check_str_isdouble(split[3]))
		triangle->side_size = ft_atof(split[3]);
	else
		return (print_error("Argument of triangle is not integer!\n"));
	// rgb
	if (check_three_arg(split[4], check_str_isdigit))
		store_rgb(split[4], &(triangle->rgb_));
	else
		return (print_error("Argument of triangle is not integer!\n"));
	rt_info->count_->tr_ += 1;
	ft_lstadd_back(&(rt_info->lst_tr_),ft_lstnew(triangle));
	return (SUCCESS);
}