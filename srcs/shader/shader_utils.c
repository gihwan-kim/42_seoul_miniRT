/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:06:43 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/05 00:20:46 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

t_vec	calc_hit_point(t_ray *ray, double *t)
{
	t_vec	hit_point;
	t_vec	multipy_result;

	multipy_result = multiply(&(ray->direction_), *t);
	hit_point = add(&(ray->origin_), &multipy_result);
	return (hit_point);
}