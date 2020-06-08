/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:29:30 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/07 13:16:10 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** check cur_obj_pos is empty
*/

int		isempty_node(t_list *cur_obj_pos)
{
	t_list *tmp;

	tmp = cur_obj_pos;
	if (cur_obj_pos == NULL)
		return (FALSE);
	return (TRUE);
}

t_list		*get_node(t_list **cur_obj_pos)
{
	t_list *result;

	result = NULL;
	if(*cur_obj_pos)
	{
		result = *cur_obj_pos;
		*cur_obj_pos = (*cur_obj_pos)->next;
	}
	return (result);
}

/*
** forward vector is camera's 3d normalized orientation vector element
*/

t_matrix	lookat(const t_c *camera)
{
	t_matrix	camera_to_world;
	t_vec		temp_up;
	t_vec		forward;
	t_vec		right;
	t_vec		up;

	matrix_zero(&camera_to_world);
	temp_up = vec_init(0, 1, 0);
	forward = camera->orient_vec_;
	forward = normalize(&forward);
	right = cross_product(&temp_up, &forward);
	right = normalize(&right);
	up = cross_product(&forward, &right);
	up = normalize(&up);
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
** use sphere and cylinder
*/

int	quadratic_formula(t_vec *quad, double *x_0, double *x_1)
{
	double d;
	double tmp;
	double q;

	d = (quad->y_ * quad->y_) - (4 * quad->x_ * quad->z_);

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
