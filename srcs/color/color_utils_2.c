/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:58:25 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/03 17:17:07 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/*
** this function is used final color
** final color is select each pixel color
*/

int	change_type_colorf_to_int(t_rgb_f *color)
{
	t_union_color	color_int;

	color_int.color_array[2] = color->r_ * 255;
	color_int.color_array[1] = color->g_ * 255;
	color_int.color_array[0] = color->b_ * 255;
	return (color_int.combination);
}

/*
** convert color which is data type int information to double
*/

// t_rgb_f	int_to_float(t_rgb *rgb_int)
// {
// 	t_rgb_f rgb_double;

// 	rgb_double.r_ = rgb_int->r_ / 255;
// 	rgb_double.g_ = rgb_int->g_ / 255;
// 	rgb_double.b_ = rgb_int->b_ / 255;
// }

// void	multi_colorf(t_rgb_f *color, double coeff)
// {
// 	color->r_ *= coeff;
// 	color->g_ *= coeff;
// 	color->b_ *= coeff;	
// }

void	multi_colorf(t_rgb_f *color, double coeff)
{
	color->r_ = fmin(color->r_ * coeff, 1);
	color->g_ *= fmin(color->g_ * coeff, 1);
	color->b_ *= fmin(color->b_ * coeff, 1);	
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
	result.b_ = fmin(a->b_ * b->b_ ,1.0);
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
