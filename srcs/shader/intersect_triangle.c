/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 10:13:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/25 11:47:11 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** triangle
** plane equation
** ax + by + cz + d = 0
** normal vector of plane  : (a, b, c), orthogonal
** d						: distance form the origin (0, 0, 0) to the plane
** 							dotproduct of vector which is normal vector of plane
** 							and vector which is vertex of triangle n * v0
*/

int	intersection_triangle(t_rt *rt_info, t_ray *cam_ray, double *t)
{
	t_tr	*triangle;
	t_vec	tr_normal;
	double	d;
	double	dot_r_d;

	if (!(triangle = get_object(rt_info->lst_pos.cur_tr)->content))
		return (SUCCESS);
	tr_normal = get_tr_normal(triangle);
	d = dot_product(&tr_normal, &(triangle->vec_1_));
	dot_r_d = dot_product(&(cam_ray->direction_), &tr_normal);
	if (dot_r_d == 0.0)
		return (print_error("Ray and object are not intersect!\n", rt_info));
	*t = (d + dot_product(&tr_normal, &(cam_ray->origin_)))
		/ dot_product(&(cam_ray->direction_), &tr_normal);
	if (t < 0)
		return (print_error("Object is behind the camera!\n", rt_info));
	if (check_inside_tr(triangle, cam_ray, t))
		return (SUCCESS);
	return (ERROR);
}


t_vec	get_tr_normal(t_tr	*tr)
{
	t_vec	result;
	t_vec	vec_2_1;
	t_vec	vec_2_3;

	vec_2_1 = subtract(&(tr->vec_1_), &(tr->vec_2_));
	vec_2_3 = subtract(&(tr->vec_3_), &(tr->vec_2_));
	result = cross_product(&vec_2_1, &vec_2_3);
	return (result);
}



static int	check_each_point(t_vec *a, t_vec *b, t_vec *p)
{
	t_vec	one;
	t_vec	two;

	one = cross_product(a, p);
	two = cross_product(b, p);

	if (dot_product(&one, &two) > 0)
		return (0);
	else
		return (1);
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
static int	check_inside_tr(t_tr *tr, t_ray *cam_ray, double *t)
{
	t_vec	b2a;
	t_vec	b2c;
	t_vec	c2a;
	t_vec	v2p;
	t_vec	p;

	p = vec_init(cam_ray->direction_.x_ * (*t) + cam_ray->origin_.x_,
		cam_ray->direction_.y_ * (*t) + cam_ray->origin_.y_,
		cam_ray->direction_.z_ * (*t) + cam_ray->origin_.z_);
	b2a = subtract(&(tr->vec_1_), &(tr->vec_2_));
	b2c = subtract(&(tr->vec_3_), &(tr->vec_2_));
	c2a = subtract(&(tr->vec_1_), &(tr->vec_3_));
	v2p = subtract(&p, &(tr->vec_2_));
	if (check_each_point(&b2a, &b2c, &v2p))
		return (0);
	v2p = subtract(&p, &(tr->vec_3_)); 
	vec_inverse(&b2c);
	if (check_each_point(&b2c, &c2a, &v2p))
		return (0);
	v2p = subtract(&p, &(tr->vec_1_)); 
	vec_inverse(&b2a);
	vec_inverse(&c2a);
	if (check_each_point(&b2a, &c2a, &v2p))
		return (0);
	return (SUCCESS);
}
