/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic_operation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 21:47:05 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/25 21:53:06 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
** order : 	a operator b
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