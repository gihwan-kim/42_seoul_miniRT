/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:29:30 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/22 23:04:51 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

int	quadratic_formula(t_vec *quadrtaic_info, t_vec *x_0, t_vec *x_1)
{
	double d;
	double tmp;
	double q;

	d = (b * b) - (4 * 1.0 * c);

	if (d < 0)
		return (ERROR);
	else if (d == 0) 	// only one t
	{
		*x_0 = - 0.5 * b / a;
		*x_1 = *x_0;
	}
	else				// two t
	{
		q = (b > 0) ? (-0.5 * (b + sqrt(d))): (-0.5 * (b - sqrt(d)));
		*x_0 = q / a;
		*x_1 = c / q;	
	}
	if (*x_0 > *x_1)
	{
		tmp = *x_0;
		*x_0 = *x_1;
		*x_1 = tmp;
	}
	return (SUCCESS);
}

t_sp		*get_sphere(t_rt *rt_info)
{
	t_sp *sphere;

	sphere = NULL;
	if (rt_info->count_->sp_)
		sphere = rt_info->lst_pos.cur_sp;
	return (sphere);
}