/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:07:11 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/28 10:21:35 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "mini_rt.h"

t_vec		multiply_by_matrix(t_vec p, t_matrix *m);
t_vec		new_vector(double x, double y, double z);
t_vec		vec_init(const double x, const double y,const double z);
t_vec		subtract(t_vec *a, t_vec *b);
t_vec		add(t_vec *a, t_vec *b);
t_vec		multiply(t_vec *a, double b);
t_vec		normalize(t_vec *vector);
t_vec		cross_product(t_vec *a, t_vec *b);
double		dot_product(t_vec *a, t_vec *b);
double		dot_product_2d(t_vec *a, t_vec *b);
double		vector_len(t_vec *a);
int			vec_compare(t_vec *a, t_vec *b);
void		vec_inverse(t_vec *a);

void	matrix_zero(t_matrix *m);

#endif