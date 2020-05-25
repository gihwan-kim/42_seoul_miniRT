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
** forward vector is camera's 3d normalized orientation vector element
*/

t_matrix	lookAt(const t_c *camera)
{
	t_matrix	camera_to_world;
	t_vec		temp_up;
	t_vec		forward;
	t_vec		right;
	t_vec		up;

	temp_up = vec_init(0, 1, 0);
	forward = camera->orient_vec;
	forward = normalize(&forward);
	right = cross_product(&temp_up, &forward);
	up = cross_product(&forward, &right);

	camera_to_world.matrix[0][0] = right.x_;
	camera_to_world.matrix[0][1] = right.y_;
	camera_to_world.matrix[0][2] = right.z_;
	camera_to_world.matrix[1][0] = up.x_;
	camera_to_world.matrix[1][1] = up.y_;
	camera_to_world.matrix[1][2] = up.z_;
	camera_to_world.matrix[2][0] = forward.x_;
	camera_to_world.matrix[2][1] = forward.y_;
	camera_to_world.matrix[2][2] = forward.z_;
	camera_to_world.matrix[3][0] = camera->vec_.x_;
	camera_to_world.matrix[3][1] = camera->vec_.y_;
	camera_to_world.matrix[3][2] = camera->vec_.z_;
	return (camera_to_world);
}

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

t_vec	add(t_vec *a, t_vec *b)
{
	t_vec	result;

	result.x_ = a->x_ + b->x_;
	result.y_ = a->y_ + b->y_;
	result.z_ = a->z_ + b->z_;
	return (result);
}

t_vec	multiply(t_vec *a, double b)
{
	t_vec	result;

	result.x_ = a->x_ * b;
	result.y_ = a->y_ * b;
	result.z_ = a->z_ * b;
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

t_vec	cross_product(t_vec *a, t_vec *b)
{
	t_vec	result;

	result.x_= a->y_ * b->z_ - a->z_ * b->y_;
	result.y_= a->z_ * b->x_ - a->x_ * b->z_;
	result.z_= a->x_ * b->y_ - a->y_ * b->x_;

	return (result);
}

double	dot_product(t_vec *a, t_vec *b)
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

/*
** compare vec a, b
** these vector is aligned same line
*/

int		vec_compare(t_vec *a, t_vec *b)
{
	double x;
	double y;
	double z;

	x = a->x_ - b->x_;
	y = a->y_ - b->y_;
	z = a->z_ - b->z_;

	if (x < 0 && y < 0 && z < 0)
		return (-1);
	else if (x > 0 && y > 0 && z > 0)
		return (1);
	else
		return (0);
}

void	vec_inverse(t_vec *a)
{
	a->x_ = a->x_ * -1;
	a->y_ = a->y_ * -1;
	a->z_ = a->z_ * -1;
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
