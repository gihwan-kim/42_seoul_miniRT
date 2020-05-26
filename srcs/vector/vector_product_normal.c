/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product_normal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 21:51:41 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/27 01:05:21 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

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
	return (a->x_ * b->x_ +  a->y_ * b->y_ +  a->z_ * b->z_);
}

double	dot_product_2d(t_vec *a, t_vec *b)
{
	return (a->x_ * b->x_ +  a->y_ * b->y_);
}
