/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:30:00 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 22:11:32 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "mini_rt.h"
# include "element.h"

/*
** pasing object, options. c files
*/

int		parsing_ambient(char **split, t_rt *rt_info);
int		parsing_resolution(char **split, t_rt *rt_info);
int		parsing_camera(char **split, t_rt *rt_info);
int		parsing_light(char **split, t_rt *rt_info);
int		parsing_sphere(char **split, t_rt *rt_info);
int		parsing_plane(char **split, t_rt *rt_info);
int		parsing_square(char **split, t_rt *rt_info);
int		parsing_cylinder(char **split, t_rt *rt_info);
int		parsing_triangle(char **split, t_rt *rt_info);
int		set_cylinder(char **split, t_cy *cylinder, t_rt *rt_info);

/*
** parsing_utils_1.c
**	: check data is integer, double, number
*/

int		parsing_rt_file(char *file, t_rt *rt_info);
int		check_str_isdigit(const char *str);
int		check_str_isdouble(const char *str);
double	ft_atof(const char *str);
size_t	get_argument_count(char **split);

/*
** parsing_utils_2.c
*/

int		check_three_arg(const char *str, int (*f)(const char*));
void	store_rgb(const char *str, t_rgb_f *rgb_ptrm, t_rt *rt_info);
void	store_vec(const char *str, t_vec *vec_ptr);
int		get_all_object_count(t_rt *rt_info);

/*
** parsing_utils_3.c
** 	: check data range
*/

double	check_size(double size, t_rt *rt_info);
double	check_light(double light, t_rt *rt_info);
int		check_normal_vec(t_vec *normal);
int		check_rgb(int color, t_rt *rt_info);
#endif
