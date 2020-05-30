/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_square.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:47:15 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/30 15:37:57 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"


t_sq	*intersection_square(t_rt *rt_info, t_ray *ray, double *t)
{
	t_vec	p;
	t_sq	*cur_square;
	double	denominator;
	t_vec	p0_l0;
	t_vec	multi_result;

	// if(!(cur_square = get_node(rt_info->lst_pos.cur_sq)->content))
	// 	return (SUCCESS);
	if (isempty_node(rt_info->lst_pos.cur_sq))
		cur_square = get_node(rt_info->lst_pos.cur_sq)->content;
	else
		return (NULL);
	denominator = dot_product(&(ray->direction_), &(cur_square->orient_vec_));
	if (denominator > 10e-7)
	{
		p0_l0 = subtract(&(cur_square->vec_), &(ray->origin_));
		*t = dot_product(&p0_l0, &(cur_square->orient_vec_)) / denominator;
		if (*t >= 0)
		{
			multi_result = multiply(&(ray->direction_), *t);
			p = add(&(ray->origin_), &multi_result);
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