/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 21:27:23 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/27 02:03:09 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

static	t_vec	get_quadrtaic_sqrt(t_ray *cam_ray, t_cy	*cylinder, int check)
{
	t_vec	quadtratic_sqrt;
	t_vec	delta;

	if (check)
	{
		quadtratic_sqrt = subtract(&(cam_ray->direction_),
							multiply(&(cylinder->orient_vec),
									dot_product(&(cam_ray->direction_), 
												&(cylinder->orient_vec))));
	}
	else
	{
		delta = subtract(&(cam_ray->origin_), &(cylinder->vec_));
		quadtratic_sqrt = subtract(&(delta),
							multiply(&(cylinder->orient_vec),
									dot_product(&(delta), 
												&(cylinder->orient_vec))));
	}
	return (quadtratic_sqrt);
}

int	check_quadratic_set_t(t_vec *quad_info, double *t, t_ray *cam_ray, t_cy *cy)
{
	double	t_0;
	double	t_1;
	t_vec	q_0;
	t_vec	q_1;
	double	check_t;

	if(!quadratic_formula(&quad_info, &t_0, &t_1))
		return (ERROR);
	if (t_0 < 0)
	{
		t_0 = t_1;
		if (t_0 < 0)
			return (ERROR);
		check
	}
	*t = t_0;
	return (SUCCESS);
}

int	intersection_cylinder(t_rt *rt_info, t_ray *cam_ray, double *t)
{
	t_vec	quadratic_info;
	t_cy	*cylinder;
	t_vec	quad_sqrt_1;
	t_vec	quad_sqrt_2;

	if (!(cylinder = get_object(rt_info->lst_pos.cur_cy)->content))
		return (SUCCESS);
	quad_sqrt_1 = get_quadrtaic_sqrt(cam_ray, cylinder, 1);
	quadratic_info.x_ = pow(vec_len(&quad_sqrt_1), 2.0);
	quad_sqrt_2 = get_quadrtaic_sqrt(cam_ray, cylinder, 0);
	quadratic_info.y_= 2.0 * dot_product(& quad_sqrt_1, &quad_sqrt_2);
	quadratic_info.z_ = pow(vector_len(&quad_sqrt_2), 2.0)
						- pow(cylinder->diameter_, 2.0);
	if (check_quadratic_set_t(&quadratic_info, t, cam_ray, cylinder))
		;
}