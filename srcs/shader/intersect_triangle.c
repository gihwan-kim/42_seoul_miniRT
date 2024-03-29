/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 10:13:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 21:25:07 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

t_vec		get_tr_normal(t_tr *tr)
{
	t_vec	result;
	t_vec	vec_2_1;
	t_vec	vec_2_3;

	vec_2_1 = subtract(&(tr->vec_1_), &(tr->vec_2_));
	vec_2_3 = subtract(&(tr->vec_3_), &(tr->vec_2_));
	result = cross_product(&vec_2_1, &vec_2_3);
	result = normalize(&result);
	return (result);
}

/*
** vec_1 : a
** vec_2 : b
** vec_3 : c
** if (cross_product(&b2a, &v2p) ● cross_product(&b2c, &v2p) > 0)
**	return (not intersect);
** if (cross_product(&b2c, &v2p) ● cross_product(&c2a, &v2p) > 0)
**	return (0);
** if (cross_product(&b2a, &v2p) ● cross_product(&c2a, &v2p) > 0)
**	return (0);
*/

static int	check_point_dot_normal(t_vec *v2v, t_vec *v2p, t_vec *tr_normal)
{
	t_vec	tmp;

	tmp = cross_product(v2v, v2p);
	if (dot_product(&tmp, tr_normal) < 0)
		return (FALSE);
	return (TRUE);
}

static int	check_inside_tr(t_tr *tr, t_ray *ray, double *t,
							t_vec *tr_normal)
{
	t_vec	b2a;
	t_vec	b2c;
	t_vec	c2a;
	t_vec	v2p;
	t_vec	p;

	p = calc_hit_point(ray, t);
	b2a = subtract(&(tr->vec_1_), &(tr->vec_2_));
	b2c = subtract(&(tr->vec_3_), &(tr->vec_2_));
	c2a = subtract(&(tr->vec_1_), &(tr->vec_3_));
	v2p = subtract(&p, &(tr->vec_2_));
	if (!check_point_dot_normal(&b2a, &v2p, tr_normal))
		return (FALSE);
	vec_inverse(&b2c);
	v2p = subtract(&p, &(tr->vec_3_));
	if (!check_point_dot_normal(&b2c, &v2p, tr_normal))
		return (FALSE);
	v2p = subtract(&p, &(tr->vec_1_));
	vec_inverse(&c2a);
	if (!check_point_dot_normal(&c2a, &v2p, tr_normal))
		return (FALSE);
	return (TRUE);
}

/*
** triangle
** plane equation
** ax + by + cz + d = 0
** normal vector of plane   : (a, b, c), orthogonal
** d						: distance form the origin (0, 0, 0) to the plane
** 							dotproduct of vector which is normal vector of plane
** 							and vector which is vertex of triangle n * v0
*/

t_tr		*intersection_triangle(t_rt *rt_info, t_ray *ray, double *t)
{
	t_tr	*triangle;
	t_vec	tr_normal;
	t_vec	tmp;
	double	d;
	double	dot_r_d;

	if (isempty_node(rt_info->lst_pos.cur_tr, rt_info->count_->tr_))
	{
		triangle = get_node(&(rt_info->lst_pos.cur_tr))->content;
	}
	else
		return (NULL);
	tr_normal = get_tr_normal(triangle);
	triangle->normal = tr_normal;
	tmp = subtract(&(triangle->vec_1_), &(ray->origin_));
	d = dot_product(&(tr_normal), &tmp);
	dot_r_d = dot_product(&(ray->direction_), &tr_normal);
	if (fabs(dot_r_d) < 10e-7)
		return (NULL);
	*t = d / dot_r_d;
	if (*t < 0)
		return (NULL);
	if (check_inside_tr(triangle, ray, t, &tr_normal))
		return (triangle);
	return (NULL);
}
