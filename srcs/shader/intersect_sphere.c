/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 10:14:59 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 19:38:53 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** d : discriminant
** a = 1
** b = 2D(O − C)
** c = |O − C|^2 − R^2
** t0 > 0, t1 > 0 : ray 가 구에 두점에서 만난다.
** t0 < 0, t1 > 0 : ray 의 원점이 구 안에 있다.
** t0 < 0, t1 < 0 : ray 의 방향벡터 반대방향에 구가 있다고.
** t0, t1 이 없다  : 교차하지 않는다.
** t0 > 0, t1 < 0 : 불가능 t0 은 항상 t1 보다 작거나 같다.
*/
t_sp	*intersection_sphere(t_rt *rt_info, t_ray *ray, double *t)
{
	t_vec	quadratic_info;
	t_vec	vec_o_to_c;
	t_sp	*cur_sphere;
	double	t_0;
	double	t_1;

	if (isempty_node(rt_info->lst_pos.cur_sp, rt_info->count_->sp_))
		cur_sphere = get_node(&(rt_info->lst_pos.cur_sp))->content;
	else
		return (NULL);
	vec_o_to_c = subtract(&(ray->origin_), &(cur_sphere->vec_));
	quadratic_info.x_ = 1.0;
	quadratic_info.y_= 2.0 * dot_product(&(ray->direction_), &vec_o_to_c);
	quadratic_info.z_ = pow(vector_len(&vec_o_to_c), 2.0) - pow(cur_sphere->diameter_, 2.0);
	if(!quadratic_formula(&quadratic_info, &t_0, &t_1))
		return (NULL);
	if (t_0 < 0)
	{
		t_0 = t_1;
		if (t_0 < 0)
			return (NULL);
	}
	*t = t_0;
	return (cur_sphere);
}
