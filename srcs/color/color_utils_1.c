/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:32:34 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/01 18:42:09 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgb_f	get_sphere_color(t_sp *sphere)
{
	return (sphere->rgb_);
}

t_rgb_f	get_square_color(t_sq *square)
{
	return (square->rgb_);
}

t_rgb_f	get_cylinder_color(t_cy *cylinder)
{
	return (cylinder->rgb_);
}

t_rgb_f	get_triangle_color(t_tr *triangle)
{
	return (triangle->rgb_);
}

t_rgb_f	get_plane_color(t_pl *plane)
{
	return (plane->rgb_);
}

// void	calc_light_amount(t_l *light, t_rgb_f *light_amount)
// {
// 	light_amount->r_ = light->rgb_.r_ * light->light_;
// 	light_amount->g_ = light->rgb_.g_ * light->light_;
// 	light_amount->b_ = light->rgb_.b_ * light->light_;
// }