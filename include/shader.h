/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:45:03 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/22 23:04:02 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H
#include "mini_rt.h"

int			make_img(t_rt *rt_info, int width, int height);
t_c			*get_camera(t_rt *rt_info);
t_matrix	lookAt(const t_c *camera);
t_ray		make_camera_ray(
							int x, int y,
							t_matrix *c2w,
							t_rt *rt_info,
							t_c *camera);
int			check_intersection(t_rt *rt_info, t_ray *camera_ray);
int			intersection_sphere(t_rt *rt_info, t_ray *camera_ray);

// intersection utils funs
int			quadratic_formula(t_vec *quadrtaic_info, t_vec *x_0, t_vec *x_1);
t_sp		*get_sphere(t_rt *rt_info);
#endif