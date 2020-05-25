/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 10:14:59 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/25 10:15:45 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

// d : discriminant

// a = 1
// b = 2D(O − C)
// c = |O − C|^2 − R^2
// t0 > 0, t1 > 0 : ray 가 구에 두점에서 만난다.
// t0 < 0, t1 > 0 : ray 의 원점이 구 안에 있다.
// t0 < 0, t1 < 0 : ray 의 방향벡터 반대방향에 구가 있다고.
// t0, t1 이 없다  : 교차하지 않는다.
// t0 > 0, t1 < 0 : 불가능 t0 은 항상 t1 보다 작거나 같다.
int	intersection_sphere(t_rt *rt_info, t_ray *camera_ray, double *t)
{
	t_vec	quadrtaic_info;
	t_vec	vec_o_to_c;
	t_sp	*cur_sphere;
	double	t_0;
	double	t_1;

	// if (!(cur_sphere = get_sphere(rt_info)))
	// 	return (SUCCESS);
	if (!(cur_sphere = get_object(rt_info->lst_pos.cur_sp)->content))
		return (SUCCESS);
	vec_o_to_c = subtract(&(camera_ray->origin_), &(camera_ray->origin_));
	quadrtaic_info.x_ = 1.0;
	quadrtaic_info.y_= 2.0 * dot_Product(&(camera_ray->direction_), &vec_o_to_c);
	quadrtaic_info.z_ = pow(vector_len(&vec_o_to_c), 2.0);
	if(!quadratic_formula(&quadrtaic_info, &t_0, &t_1))
		return (ERROR);
	if (t_0 < 0)
	{
		t_0 = t_1;
		if (t_0 < 0)
			return (ERROR);
	}
	*t = t_0;
	return (SUCCESS);
}

int	quadratic_formula(t_vec *quad, double *x_0, double *x_1)
{
	double d;
	double tmp;
	double q;

	d = (quad->y_) * quad->y_)) - (4 * 1.0 * quad->z_);

	if (d < 0)
		return (ERROR);
	else if (d == 0) 	// only one t
	{
		*x_0 = - 0.5 * quad->y_ / quad->x_;
		*x_1 = *x_0;
	}
	else				// two t
	{
		q = ((quad->y_) > 0.0) ? -0.5 * (quad->y_ + sqrt(d)) : -0.5 * (quad->y_ - sqrt(d));
		*x_0 = q / quad->x_;
		*x_1 = quad->z_ / q;	
	}
	if (*x_0 > *x_1)
	{
		tmp = *x_0;
		*x_0 = *x_1;
		*x_1 = tmp;
	}
	return (SUCCESS);
}
