/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 14:47:42 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/07 13:16:33 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"


/*
** normal 은 물체 반대방향을 가리키면안됨
** camera 쪽을 바라봐야함
** camera_ray direction 과 normal 의 각은 둔각이 되어야한다.
*/

t_vec	make_plane_normal(t_pl *plane)
{
	t_vec	normal;

	normal = plane->orient_vec_;
	return (normal);
}

t_vec	make_sphere_normal(t_sp *sphere, t_vec *hit_p)
{
	t_vec	normal;
	normal = subtract(hit_p, &(sphere->vec_));
	normal = normalize(&normal);
	return (normal);
}

t_vec	make_cylinder_normal(t_cy *cylinder, t_vec *hit_p)
{
	t_vec	normal;
	t_vec	axis;
	t_vec	cy_vec_to_hit_p;
	double	coeff;

	axis = cylinder->orient_vec_;
	cy_vec_to_hit_p = subtract(hit_p, &(cylinder->vec_));
	coeff = dot_product(&cy_vec_to_hit_p, &axis);
	axis = multiply(&axis, coeff);
	vec_inverse(&axis);
	normal = add(&cy_vec_to_hit_p, &axis);
	normal = normalize(&normal);
	return (normal);
}

t_vec	make_square_normal(t_sq *square)
{
	t_vec	normal;

	normal = square->orient_vec_;
	return (normal);
}

t_vec	make_triangle_normal(t_tr *triangle)
{
	t_vec	normal;

	normal = get_tr_normal(triangle);
	return (normal);
}