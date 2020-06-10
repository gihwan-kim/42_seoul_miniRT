/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:31:40 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 19:50:57 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

double		check_size(double size, t_rt *rt_info)
{
	if (size >= 0)
		return (size);
	else
	{
		print_error(22, "size or diameter range is positive!", rt_info);
		exit(EXIT_FAILURE);
	}
}

double		check_light(double light, t_rt *rt_info)
{
	if (10e-7 <= light && light <= 1.0)
		return (light);
	else
	{
		print_error(22, "light range is [0.0,1.0]!", rt_info);
		exit(EXIT_FAILURE);
	}
}

static int	check_point(double coordinate)
{
	if (-1.0 <= coordinate && coordinate <= 1.0)
		return (TRUE);
	else
		return (FALSE);
}

int			check_normal_vec(t_vec *normal)
{
	if (check_point(normal->x_)
		&& check_point(normal->y_)
		&& check_point(normal->z_))
		return (TRUE);
	else
		return (FALSE);
}

int			check_rgb(int color, t_rt *rt_info)
{
	if (0 <= color && color <= 255)
		return (TRUE);
	else
	{
		print_error(22, "rgb range is [0,255]!", rt_info);
		exit(EXIT_FAILURE);
	}
}
