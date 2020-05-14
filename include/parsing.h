/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:30:00 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/14 21:26:12 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "mini_rt.h"
int		parsing_rt_file(char *file, t_rt *rt_info);
int		check_str_isdigit(const char *str);
int		check_str_isdouble(const char *str);
int		check_three_arg(const char *str, int (*f)(const char*));
double	ft_atof(const char *str);
size_t	get_argument_count(char **split);
int		parsing_ambient(char **split, t_rt *rt_info);
int		parsing_resolution(char **split, t_rt *rt_info);
int		parsing_camera(char **split, t_rt *rt_info);
void	store_rgb(const char *str, t_rgb *rgb_ptr);
void	store_vec(const char *str, t_vec *vec_ptr);

#endif