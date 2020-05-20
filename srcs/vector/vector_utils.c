/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:06:25 by gihwan-kim        #+#    #+#             */
/*   Uvecdated: 2020/05/19 17:33:55 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"


t_vec	*mult_Vec_Matrix(t_vec vec, t_matrix m)
{
	t_vec *return_val;
	double x;
	double y;
	double z;

	x = vec.x_ * m.d[0][0] + vec.y_ * m.d[1][0] + vec.z_ * m.d[2][0] + m.d[3][0];
	y = vec.x_ * m.d[0][1] + vec.y_ * m.d[1][1] + vec.z_ * m.d[2][1] + m.d[3][1];
	z = vec.x_ * m.d[0][2] + vec.y_ * m.d[1][2] + vec.z_ * m.d[2][2] + m.d[3][2];
	return_val = new_vector(x, y, z);
	return (return_val);
}


t_vec	*new_vector(double x, double y, double z)
{
	t_vec *new_vec;

	new_vec = ft_calloc(1, sizeof(t_vec));
	new_vec->x_ = x;
	new_vec->y_ = y;
	new_vec->z_ = z;
	return (new_vec);
}
