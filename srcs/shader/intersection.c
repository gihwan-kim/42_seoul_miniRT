/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:54:53 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/22 23:08:55 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"


 	// d : discriminant

	// a = 1
	// b = 2D(O − C)
	// c = |O − C|^2 − R^2
int	intersection_sphere(t_rt *rt_info, t_ray *camera_ray)
{
	t_vec	quadrtaic_info;
	t_vec	vec_o_to_c;
	t_sp	*cur_sphere;
	double	t_0;
	double	t_1;

	
	if (!(cur_sphere = get_sphere(rt_info)))
		return (ERROR);
	vec_o_to_c = subtract(&(camera_ray->origin_), &(camera_ray->origin_));
	quadrtaic_info.x_ = 1.0;
	quadrtaic_info.y_= 2.0 * dot_Product(&(camera_ray->direction_), &vec_o_to_c);
	quadrtaic_info.z_ = pow(vector_len(&vec_o_to_c), 2.0);
	if(!quadratic_formula(&quadrtaic_info, &t_0, &t_1))
		return (ERROR);
	return (SUCCESS);
	// lst_sp 에 다시 넣어주기
}