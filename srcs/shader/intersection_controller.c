/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_controller.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:54:53 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/25 21:45:47 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

int		intersection_controller(t_rt *rt_info, t_ray *camera_ray, double *tnear)
{
	double	cur_t;
	int		intersection_loop;
	int		i;

	i = -1;
	intersection_loop = get_all_object_count(rt_info);
	while (++i < intersection_loop)
	{
		if (check_intersection(rt_info, camera_ray, &cur_t))
		{
			if (cur_t < *tnear)
				*tnear = cur_t;
		}
		else
			return (0);
	}
}

int		check_intersection(t_rt *rt_info, t_ray *camera_ray, double *t)
{
	if (intersection_sphere(rt_info, camera_ray, t))
	{

	}
	else if (intersection_plane(rt_info, camera_ray, t))
	{

	}
	else if (intersection_square(rt_info, camera_ray, t))
	{

	}
	else if (intersection_cylinder(rt_info, camera_ray, t))
	{

	}
	else if (intersection_triangle(rt_info, camera_ray, t))
	{

	}
	return (0);
}