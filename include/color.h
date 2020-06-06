/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:59:51 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/05 15:58:13 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
#define COLOR_H
#include "mini_rt.h"

/*
** color_utils_2.c
*/
t_rgb_f	colorf_multi_colorf(t_rgb_f *a, t_rgb_f *b);
// t_rgb_f	int_to_float(t_rgb *rgb_int);
t_rgb_f	multi_colorf(t_rgb_f *color, double coeff);
t_rgb_f	add_color(t_rgb_f *a, t_rgb_f *b);
int		change_type_colorf_to_int(t_rgb_f *color);
// void	calc_light_amount(t_l *light, t_rgb_f *light_amount);
t_rgb_f	init_color(double val);

/*
** color_utils_1.c
*/
t_rgb_f	get_sphere_color(t_sp *sphere);
t_rgb_f	get_square_color(t_sq *square);
t_rgb_f	get_cylinder_color(t_cy *cylinder);
t_rgb_f	get_triangle_color(t_tr *triangle);
t_rgb_f	get_plane_color(t_pl *plane);
#endif