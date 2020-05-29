/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 10:14:42 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/29 10:41:10 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** t = (p_0 - l_0) ● n / (l ● n)
** dot porudct : |a||b|cos
** when compare 0.0 in floating number. don't use equal
*/

t_pl *intersection_plane(t_rt *rt_info, t_ray *camera_ray, double *t)
{
	t_pl	*cur_plane;
	double	denominator;
	t_vec	p0_l0;

	// if(!(cur_plane = get_object(rt_info->lst_pos.cur_pl)->content))
	// 	return (SUCCESS);
	if (get_object(rt_info->lst_pos.cur_pl))
		cur_plane = get_object(rt_info->lst_pos.cur_pl)->content;
	else
		return (NULL);
	denominator = dot_product(&(camera_ray->direction_), &(cur_plane->orient_vec_));
	// printf("denominator : %f\n", denominator);
	if (fabs(denominator) > 10e-7)
	{
		p0_l0 = subtract(&(cur_plane->vec_), &(camera_ray->origin_));
		*t = dot_product(&p0_l0, &(cur_plane->orient_vec_)) / denominator;
		// printf("t : %f\n", *t);
		if (*t >= 0)
			return (cur_plane);
	}
	return (NULL);
}
