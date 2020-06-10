/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 21:26:34 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 21:28:47 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
** In modern C if two structs is same data type one struct can be assignment-
** to another struct.
** Each memeber assignment to another struct.
** If member is array type. assignment is same
*/

t_vec	vec_init(const double x, const double y, const double z)
{
	t_vec vector;

	vector.x_ = x;
	vector.y_ = y;
	vector.z_ = z;
	return (vector);
}

double	vector_len(t_vec *a)
{
	return (sqrt(pow(a->x_, 2.0) + pow(a->y_, 2.0) + pow(a->z_, 2.0)));
}

t_vec	multiply_by_matrix(t_vec vec, t_matrix *m)
{
	t_vec	return_val;
	double	x;
	double	y;
	double	z;

	x = vec.x_ * m->matrix[0][0]
		+ vec.y_ * m->matrix[1][0]
		+ vec.z_ * m->matrix[2][0]
		+ m->matrix[3][0];
	y = vec.x_ * m->matrix[0][1]
		+ vec.y_ * m->matrix[1][1]
		+ vec.z_ * m->matrix[2][1]
		+ m->matrix[3][1];
	z = vec.x_ * m->matrix[0][2]
		+ vec.y_ * m->matrix[1][2]
		+ vec.z_ * m->matrix[2][2]
		+ m->matrix[3][2];
	return_val = vec_init(x, y, z);
	return (return_val);
}

void	vec_inverse(t_vec *a)
{
	a->x_ = a->x_ * -1;
	a->y_ = a->y_ * -1;
	a->z_ = a->z_ * -1;
}

void	matrix_zero(t_matrix *m)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (j++ < 4)
			m->matrix[i][j] = 0.0;
	}
}
