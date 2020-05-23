/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:29:30 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/23 22:30:55 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

int	quadratic_formula(t_vec *quad, double *x_0, double *x_1)
{
	double d;
	double tmp;
	double q;

	d = (quad->y_) * quad->y_)) - (4 * 1.0 * quad->z_);

	if (d < 0)
		return (ERROR);
	else if (d == 0) 	// only one t
	{
		*x_0 = - 0.5 * quad->y_ / quad->x_;
		*x_1 = *x_0;
	}
	else				// two t
	{
		q = ((quad->y_) > 0.0) ? -0.5 * (quad->y_ + sqrt(d)) : -0.5 * (quad->y_ - sqrt(d));
		*x_0 = q / quad->x_;
		*x_1 = quad->z_ / q;	
	}
	if (*x_0 > *x_1)
	{
		tmp = *x_0;
		*x_0 = *x_1;
		*x_1 = tmp;
	}
	return (SUCCESS);
}

t_list		*get_object(t_list *cur_obj_pos)
{
	t_list *tmp;
	
	tmp = cur_obj_pos;
	if (cur_obj_pos == NULL)
		return (NULL);
	cur_obj_pos = cur_obj_pos->next;
	return (tmp);
}

t_sp		*get_sphere(t_rt *rt_info)
{
	t_sp *sphere;

	sphere = NULL;
	if (rt_info->count_->sp_)
		sphere = rt_info->lst_pos.cur_sp->content;
	return (sphere);
}

t_vec	get_tr_normal(t_tr	*tr)
{
	t_vec	result;
	t_vec	vec_2_1;
	t_vec	vec_2_3;

	vec_2_1 = subtract(&(tr->vec_1_), &(tr->vec_2_));
	vec_2_3 = subtract(&(tr->vec_3_), &(tr->vec_2_));
	result = crossProduct(&vec_2_1, &vec_2_3);
	return (result);
}