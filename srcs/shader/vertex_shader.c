/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_shader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:31:38 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/22 23:04:18 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** make_camera_ray() 
** raster space -> NDC space -> screen space -> world space
** 1. change pixel point to wolrd psace coordinate
**		result : pixel_x, pixel_y (= called point "P")
** 2. apply c2w(camera to world matrix) to O(camera origin) and p (= 0,0,0)
** 3. make OP vector 
**		P - O
** 4. make ray directon vectokr
**		normalzie OP vectr
*/

t_ray		make_camera_ray(int x, int y,
							t_matrix *c2w,
							t_rt *rt_info,
							t_c *camera)
{
	t_ray	camera_ray;
	double	pixel_x;
	double	pixel_y;
	double	width;
	double	height;

	width = (double)(rt_info->t_r_->size_x_);
	height = (double)(rt_info->t_r_->size_y_);
	pixel_x = (2 * (x + 0.5) / width - 1) * tan(camera->fov_ / 2 * M_PI / 180) * (width / height);
	pixel_y = (1 - 2 * (y + 0.5) / height) * tan(camera->fov_ / 2 * M_PI / 180);
	camera_ray.origin_ = multiply_by_matrix(vec_init(0,0,0), c2w);
	camera_ray.direction_ = vec_init(pixel_x, pixel_y, 1);
	camera_ray.direction_ = multiply_by_matrix(camera_ray.direction_, c2w);
	camera_ray.direction_ = subtract(&(camera_ray.direction_), &(camera_ray.origin_));
	camera_ray.direction_ = normalize(&(camera_ray.direction_));
	return (camera_ray);
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
	right = crossProduct(&temp_up, &forward);
	up = crossProduct(&forward, &right);

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
** select camera in list
*/

t_c		*get_camera(t_rt *rt_info)
{
	t_c *camera;

	camera = NULL;
	if (rt_info->count_->c_)
		camera = rt_info->lst_pos.cur_c;
	return (camera);
}

int		check_intersection(t_rt *rt_info, t_ray *camera_ray)
{
	if (intersection_sphere(rt_info, camera_ray))
	{

	}
	else if (intersection_plane(rt_info, camera_ray))
	{

	}
	else if (intersection_square(rt_info, camera_ray))
	{

	}
	else if (intersection_cylinder(rt_info, camera_ray))
	{

	}
	else if (intersection_triangle(rt_info, camera_ray))
	{

	}
}