/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:45:03 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/11 20:15:13 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H
# include "mini_rt.h"
# include "bmp.h"
# include "element.h"

/*
** shader.c
*/

int			make_img(t_rt *rt_info, t_c *camera, int width, int height);

/*
** vertex_shader.c
*/

t_ray		make_camera_ray(int x, int y, t_matrix *c2w, t_rt *rt_info);

/*
** intersection object c files
*/

int			intersection_controller(t_rt *rt_info,
									t_ray *ray,
									t_phit *h_obj,
									double *tnear);
void		*check_intersection(t_rt *rt_info,
								t_ray *ray,
								t_e_obj *type,
								double *t);
t_sp		*intersection_sphere(t_rt *rt_info, t_ray *ray, double *t);
t_pl		*intersection_plane(t_rt *rt_info, t_ray *ray, double *t);
t_sq		*intersection_square(t_rt *rt_info, t_ray *ray, double *t);
t_cy		*intersection_cylinder(t_rt *rt_info, t_ray *ray, double *t);
t_tr		*intersection_triangle(t_rt *rt_info, t_ray *ray, double *t);

/*
** intersection_utils.c
*/

int			quadratic_formula(t_vec *quadratic_info, double *x_0, double *x_1);
t_matrix	lookat(const t_c *camera);
int			isempty_node(t_list *cur_obj_pos, int obj_number);
t_list		*get_node(t_list **cur_obj_pos);
t_vec		get_tr_normal(t_tr	*tr);

/*
** pixel_shader.c
*/
t_rgb		pixel_shader(t_rt *rt_info,
						t_ray *camera_ray,
						double *t,
						t_phit *obj_info);

/*
** make_normal.c
*/

t_vec		make_plane_normal(t_pl *plane);
t_vec		make_sphere_normal(t_sp *sphere, t_vec *hit_p);
t_vec		make_cylinder_normal(t_cy *cylinder, t_vec *hit_p);
t_vec		make_square_normal(t_sq *square);
t_vec		make_triangle_normal(t_tr *triangle);

/*
** shader_utils.c
*/

t_vec		calc_hit_point(t_ray *ray, double *t);
#endif
