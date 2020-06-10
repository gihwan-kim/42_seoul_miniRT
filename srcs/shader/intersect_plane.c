/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 10:14:42 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 20:46:07 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** t = (p_0 - l_0) ● n / (l ● n)
** dot porudct : |a||b|cos
** when compare 0.0 in floating number. don't use equal
*/

t_pl	*intersection_plane(t_rt *rt_info, t_ray *ray, double *t)
{
	t_pl	*cur_plane;
	double	denominator;
	t_vec	p0_l0;

	if (isempty_node(rt_info->lst_pos.cur_pl, rt_info->count_->pl_))
		cur_plane = get_node(&(rt_info->lst_pos.cur_pl))->content;
	else
		return (NULL);
	denominator = dot_product(&(ray->direction_), &(cur_plane->orient_vec_));
	if (fabs(denominator) > 10e-7)
	{
		p0_l0 = subtract(&(cur_plane->vec_), &(ray->origin_));
		*t = dot_product(&p0_l0, &(cur_plane->orient_vec_)) / denominator;
		if (*t >= 0)
			return (cur_plane);
	}
	return (NULL);
}
