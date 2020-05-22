/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:07:11 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/22 21:04:31 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "mini_rt.h"

typedef struct	s_matrix
{
	double matrix[4][4];
}				t_matrix;

t_vec		multiply_by_matrix(t_vec p, t_matrix *m);
t_vec		new_vector(double x, double y, double z);
t_vec		vec_init(const double x, const double y,const double z);
t_vec		subtract(t_vec *a, t_vec *b);
t_vec		normalize(t_vec *vector);
t_vec		crossProduct(t_vec *a, t_vec *b);
double		dot_Product(t_vec *a, t_vec *b);
double		vector_len(t_vec *a);


#endif