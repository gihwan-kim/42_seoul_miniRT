/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:54:53 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/23 22:47:33 by gihwan-kim       ###   ########.fr       */
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

// t = (p_0 - l_0) ● n / (l ● n)
// dot porudct : |a||b|cos
// when compare 0.0 in floating number. don't use equal

int intersection_plane(t_rt *rt_info, t_ray *camera_ray, double *t)
{
	t_pl	*cur_plane;
	double	denominator;
	t_vec	p0_l0;

	if(!(cur_plane = get_object(rt_info->lst_pos.cur_pl)->content))
		return (SUCCESS);
	denominator = dot_product(&(camera_ray->direction_), &(cur_plane->orient_vec));
	if (denominator > 10e-7)
	{
		p0_l0 = subtract(&(cur_plane->vec_), &(camera_ray->origin_));
		*t = dot_Product(&p0_l0, &(cur_plane->orient_vec)) / denominator;
		if (*t >= 0)
			return (SUCCESS);
	}
	return (print_error("Ray and plane are not intersect", rt_info));
}

int	intersection_trinangle(t_rt *rt_info, t_ray *camera_ray, double *t)
{
	t_tr	*triangle;
	t_vec	tr_normal;
	double	denominator;
	t_vec	p0_l0;

	if (!(triangle = get_object(rt_info->lst_pos.cur_tr)->content))
		return (SUCCESS);
	tr_normal = get_tr_normal(triangle);
	denominator =  dot_product(&(camera_ray->direction_), &(tr_normal));
	if (denominator > 10e-7)
	{

		if (*t >= 0)
			return (SUCCESS);
	}
}