/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:09:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/29 18:18:46 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** hit_n is orthogonal to hit point
** normal 은 물체 반대방향을 가리키면안됨
** camera 쪽을 바라봐야함
** camera_ray direction 과 normal 의 각은 둔각이 되어야한다.
*/
static void	calc_normal(t_rt *rt_info,
						t_vec *hit_p,
						t_vec *hit_n,
						t_ray *cam_ray)
{
	t_e_obj hit_obj_type;
	void	*obj;

	hit_obj_type = rt_info->img_.hit_obj.type;
	obj = rt_info->img_.hit_obj.obj;
	if (hit_obj_type = plane)
		make_plane_normal((t_pl*)plane, hit_n, hit_p);
	else if (hit_obj_type = sphere)
		make_sphere_normal((t_sp*)sphere, hit_n, hit_p);
	else if (hit_obj_type = cylinder)
		make_cylinder_normal((t_cy*)cylinder, hit_n, hit_p);
	else if (hit_obj_type = square)
		make_square_normal((t_sq*)square, hit_n, hit_p);
	else if (hit_obj_type = triangle)
		make_triangle_normal((t_tr*)triangle, hit_n, hit_p);
	if (dot_product(hit_n, &(cam_ray->direction_)) > 0)
		vec_inverse(hit_n);
}

static	int calc_color(t_l *light_source, t_vec *hit_point)
{
	int color;
	t_vec	light_dir;

	light_dir = subtract(&(light_source->vec_), hit_point);
	light_dir = normalize(&light_dir);
	return (color);
}

int			pixel_shader(t_rt *rt_info, t_ray *camera_ray, double *t)
{
	t_vec	hit_point;
	t_vec	hit_normal;
	t_vec	p_dot_d;
	int		color;

	p_dot_d = multiply(&(camera_ray->direction_), *t);
	hit_point = add(&(camera_ray->origin_), &p_dot_d);
	calc_normal(rt_info, &hit_point, &hit_normal, camera_ray);
	return (0);
}
