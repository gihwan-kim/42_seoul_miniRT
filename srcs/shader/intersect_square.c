/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_square.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:47:15 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/27 01:05:21 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"


int	intersection_square(t_rt *rt_info, t_ray *camera_ray, double *t)
{
	t_vec	p;
	t_sq	*cur_square;
	double	denominator;
	t_vec	p0_l0;

	if(!(cur_square = get_object(rt_info->lst_pos.cur_sq)->content))
		return (SUCCESS);
	denominator = dot_product(&(camera_ray->direction_), &(cur_square->orient_vec));
	if (denominator > 10e-7)
	{
		p0_l0 = subtract(&(cur_square->vec_), &(camera_ray->origin_));
		*t = dot_product(&p0_l0, &(cur_square->orient_vec)) / denominator;
		if (*t >= 0)
		{
			p = add(&(camera_ray->origin_), &multiply(&(camera_ray->direction_), *t));
			if (fabs(p.x_ - cur_square->vec_.x_) > (cur_square->side_size / 2))
				return (0);
			if (fabs(p.x_ - cur_square->vec_.x_) > (cur_square->side_size / 2))
				return (0);
			if (fabs(p.x_ - cur_square->vec_.x_) > (cur_square->side_size / 2))
				return (0);
			return (SUCCESS);
		}
		else
			return (0);	
	}
}