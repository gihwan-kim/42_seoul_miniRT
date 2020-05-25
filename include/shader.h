/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:45:03 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/25 11:35:59 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H
#include "mini_rt.h"
# define t_infinity 424242.0

int		make_img(t_rt *rt_info, int width, int height);
t_c		*get_camera(t_rt *rt_info);
t_ray	make_camera_ray(
							int x, int y,
							t_matrix *c2w,
							t_rt *rt_info,
							t_c *camera);
int		intersection_controller(t_rt *rt_info, t_ray *camera_ray, double *t);
int		check_intersection(t_rt *rt_info, t_ray *camera_ray, double *t)
int		intersection_sphere(t_rt *rt_info, t_ray *camera_ray, double *t);
int		intersection_plane(t_rt *rt_info, t_ray *camera_ray, double *t);
int		intersection_square(t_rt *rt_info, t_ray *camera_ray, double *t);
int		intersection_cylinder(t_rt *rt_info, t_ray *camera_ray, double *t);
int		intersection_triangle(t_rt *rt_info, t_ray *camera_ray, double *t);

// intersection utils funs
int		quadratic_formula(t_vec *quadrtaic_info, double *x_0, double *x_1);
// t_sp	*get_sphere(t_rt *rt_info);
t_list	*get_object(t_list *cur_obj_pos);
t_vec	get_tr_normal(t_tr	*tr);
#endif