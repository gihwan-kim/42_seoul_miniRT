/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:32:34 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/29 17:07:04 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

void	multi_colorf()
{
	
}

void	calc_light_amount(t_l *light, t_rgb_f *light_amount)
{
	light_amount->r_ = light->rgb_->r_ * light->light_;
	light_amount->g_ = light->rgb_->g_ * light->light_;
	light_amount->b_ = light->rgb_->b_ * light->light_;
}