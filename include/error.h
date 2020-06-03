/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:54:27 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/03 14:43:30 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

#include "mini_rt.h"

int		print_error(int errno, char* comment, t_rt *rt_info);
int		print_error_comment(char* comment, t_rt *rt_info);
int		print_error_no(int errno, t_rt *rt_info);
int		print_error_nofree(int errno, char* comment);
void	rt_info_free(t_rt *rt_info);


void	print_light(t_l *light);
void	print_rgb_f(const t_rgb_f *rgb);
void	print_vec(const t_vec *vec);
void	print_matrix(t_matrix *m);
#endif