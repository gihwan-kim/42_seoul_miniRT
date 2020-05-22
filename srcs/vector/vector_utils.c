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

/*
** 최신 c 는 같은 데이터 형이라면 한 구조체를 다른 구조체에 대입하는 것을 허용한다.
** 각 멤버의 값이 대응되어 대입된다.
** 멤버가 배열일 경우도 대입된다.
*/

/*
** In modern C if two structs is same data type one struct can be assignment-
** to another struct.
** Each memeber assignment to another struct.
** If member is array type. assignment is same
*/

t_vec	vec_init(const double x, const double y,const double z)
{
	t_vec vector;

	vector.x_ = x;
	vector.y_ = y;
	vector.z_ = z;
	return (vector);
}

/*
** subtrac()
** 	: a - b
*/

t_vec	subtract(t_vec *a, t_vec *b)
{
	t_vec	result;

	result.x_ = a->x_ - b->x_;
	result.y_ = a->y_ - b->y_;
	result.z_ = a->z_ - b->z_;
	return (result);
}

t_vec	normalize(t_vec *vector)
{
	double	vector_len;
	t_vec	result;

	vector_len = sqrt(
						vector->x_ * vector->x_ 
						+ vector->x_ * vector->x_ 
						+ vector->x_ * vector->x_ );
	result.x_ = vector->x_ / vector_len;
	result.y_ = vector->y_ / vector_len;
	result.z_ = vector->z_ / vector_len;
	return (result);
}

t_vec	cross_Product(t_vec *a, t_vec *b)
{
	t_vec	result;

	result.x_= a->y_ * b->z_ - a->z_ * b->y_;
	result.y_= a->z_ * b->x_ - a->x_ * b->z_;
	result.z_= a->x_ * b->y_ - a->y_ * b->x_;

	return (result);
}

double	dot_Product(t_vec *a, t_vec *b)
{
	return (a->x_ * b->x_ +  a->x_ * b->x_ +  a->x_ * b->x_);
}

double	vector_len(t_vec *a)
{
	return sqrt(pow(a->x_, 2) + pow(a->y_, 2) + pow(a->z_, 2));
}

t_vec	mult_Vec_Matrix(t_vec vec, t_matrix *m)
{
	t_vec return_val;
	double x;
	double y;
	double z;

	x = vec.x_ * m->d[0][0] + vec.y_ * m->d[1][0] + vec.z_ * m->d[2][0] + m->d[3][0];
	y = vec.x_ * m->d[0][1] + vec.y_ * m->d[1][1] + vec.z_ * m->d[2][1] + m->d[3][1];
	z = vec.x_ * m->d[0][2] + vec.y_ * m->d[1][2] + vec.z_ * m->d[2][2] + m->d[3][2];
	return_val = vec_init(x, y, z);
	return (return_val);
}

// t_vec	*new_vector(double x, double y, double z)
// {
// 	t_vec *new_vec;

// 	new_vec = ft_calloc(1, sizeof(t_vec));
// 	new_vec->x_ = x;
// 	new_vec->y_ = y;
// 	new_vec->z_ = z;
// 	return (new_vec);
// }
