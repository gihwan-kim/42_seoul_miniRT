/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_square.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:47:15 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 17:58:02 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

t_sq	*intersection_square(t_rt *rt_info, t_ray *ray, double *t)
{
	t_vec	p;
	t_sq	*cur_square;
	double	denominator;
	t_vec	p0_l0;

	if (isempty_node(rt_info->lst_pos.cur_sq, rt_info->count_->sq_))
		cur_square = get_node(&(rt_info->lst_pos.cur_sq))->content;
	else
		return (NULL);
	denominator = dot_product(&(ray->direction_), &(cur_square->orient_vec_));
	if (fabs(denominator) > 10e-7)
	{
		p0_l0 = subtract(&(cur_square->vec_), &(ray->origin_));
		*t = dot_product(&p0_l0, &(cur_square->orient_vec_)) / denominator;
		if (*t >= 0)
		{
			p = calc_hit_point(ray, t);
			if (fabs(p.x_ - cur_square->vec_.x_) > (cur_square->side_size / 2))
				return (NULL);
			if (fabs(p.y_ - cur_square->vec_.y_) > (cur_square->side_size / 2))
				return (NULL);
			if (fabs(p.z_ - cur_square->vec_.z_) > (cur_square->side_size / 2))
				return (NULL);
			return (cur_square);
		}
		else
			return (NULL);	
	}
	return (NULL);
}