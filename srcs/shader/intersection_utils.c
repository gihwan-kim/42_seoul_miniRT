/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:29:30 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/25 21:48:56 by gihwan-kim       ###   ########.fr       */
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

t_matrix	lookAt(const t_c *camera)
{
	t_matrix	camera_to_world;
	t_vec		temp_up;
	t_vec		forward;
	t_vec		right;
	t_vec		up;

	temp_up = vec_init(0, 1, 0);
	forward = camera->orient_vec;
	forward = normalize(&forward);
	right = cross_product(&temp_up, &forward);
	up = cross_product(&forward, &right);

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

// t_sp		*get_sphere(t_rt *rt_info)
// {
// 	t_sp *sphere;

// 	sphere = NULL;
// 	if (rt_info->count_->sp_)
// 		sphere = rt_info->lst_pos.cur_sp->content;
// 	return (sphere);
// }

