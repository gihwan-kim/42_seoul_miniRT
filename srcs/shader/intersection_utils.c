/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:29:30 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/28 14:26:06 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

t_list		*get_object(t_list *cur_obj_pos)
{
	t_list *tmp;
	
	tmp = cur_obj_pos;
	if (cur_obj_pos == NULL)
		return (NULL);
	cur_obj_pos = cur_obj_pos->next;
	return (tmp);
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
	// temp_up = normalize(&temp_up);
	right = cross_product(&temp_up, &forward);
	right = normalize(&right);
	up = cross_product(&forward, &right);
	up = normalize(&up);
	print_vec(&(camera->vec_));
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

	d = (quad->y_ * quad->y_) - (4 * 1.0 * quad->z_);

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

// t_sp		*get_sphere(t_rt *rt_info)
// {
// 	t_sp *sphere;

// 	sphere = NULL;
// 	if (rt_info->count_->sp_)
// 		sphere = rt_info->lst_pos.cur_sp->content;
// 	return (sphere);
// }

