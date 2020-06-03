/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 10:14:42 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/03 13:55:01 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** t = (p_0 - l_0) ● n / (l ● n)
** dot porudct : |a||b|cos
** when compare 0.0 in floating number. don't use equal
*/

t_pl *intersection_plane(t_rt *rt_info, t_ray *ray, double *t)
{
	t_pl	*cur_plane;
	double	denominator;
	t_vec	p0_l0;

	// if(!(cur_plane = get_node(rt_info->lst_pos.cur_pl)->content))
	// 	return (SUCCESS);
	// write(1, "1\n", 2);
	if (isempty_node(rt_info->lst_pos.cur_pl))
		// cur_plane = get_node(rt_info->lst_pos.cur_pl)->content;
		cur_plane = get_node(&(rt_info->lst_pos.cur_pl))->content;
	else
		return (NULL);
	// write(1, "2\n", 2);
	denominator = dot_product(&(ray->direction_), &(cur_plane->orient_vec_));
	// printf("denominator : %f\n", denominator);
	if (fabs(denominator) > 10e-7)
	{
		// write(1, "3\n", 2);
		p0_l0 = subtract(&(cur_plane->vec_), &(ray->origin_));
		*t = dot_product(&p0_l0, &(cur_plane->orient_vec_)) / denominator;
		// printf("t : %f\n", *t);
		// write(1, "4\n", 2);
		if (*t >= 0)
			return (cur_plane);
	}
	return (NULL);
}
