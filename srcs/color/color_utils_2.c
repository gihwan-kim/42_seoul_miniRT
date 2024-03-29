/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:58:25 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 21:47:39 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/*
** this function is used final color
** final color is select each pixel color
*/

int		change_type_colorf_to_int(t_rgb_f *color)
{
	t_union_color	color_int;

	color_int.color_array[2] = color->r_ * 256;
	color_int.color_array[1] = color->g_ * 256;
	color_int.color_array[0] = color->b_ * 256;
	return (color_int.combination);
}

t_rgb_f	multi_colorf(t_rgb_f *color, double coeff)
{
	t_rgb_f result;

	result.r_ = fmin(color->r_ * coeff, 1);
	result.g_ = fmin(color->g_ * coeff, 1);
	result.b_ = fmin(color->b_ * coeff, 1);
	return (result)	;
}

/*
** fmin(a, b)
** if a > b
** fmin retun b
*/

t_rgb_f	colorf_multi_colorf(t_rgb_f *a, t_rgb_f *b)
{
	t_rgb_f result;

	result.r_ = fmin(a->r_ * b->r_, 1.0);
	result.g_ = fmin(a->g_ * b->g_, 1.0);
	result.b_ = fmin(a->b_ * b->b_, 1.0);
	return (result);
}

t_rgb_f	add_color(t_rgb_f *a, t_rgb_f *b)
{
	t_rgb_f result;

	result.r_ = fmin(a->r_ + b->r_, 0.99);
	result.g_ = fmin(a->g_ + b->g_, 0.99);
	result.b_ = fmin(a->b_ + b->b_, 0.99);
	return (result);
}

t_rgb_f	init_color(double val)
{
	t_rgb_f result;

	result.r_ = val;
	result.g_ = val;
	result.b_ = val;
	return (result);
}
