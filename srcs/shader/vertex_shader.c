/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_shader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:31:38 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/01 18:07:16 by gihwan-kim       ###   ########.fr       */
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
	pixel_x = (2 * (x + 0.5) / width - 1) * tan(camera->fov_ / 2 * M_PI / 180)
				* (width / height);
	pixel_y = (1 - 2 * (y + 0.5) / height) * tan(camera->fov_ / 2 * M_PI / 180);
	camera_ray.origin_ = multiply_by_matrix(vec_init(0,0,0), c2w);
	camera_ray.direction_ = vec_init(pixel_x, pixel_y, 1);
	camera_ray.direction_ = multiply_by_matrix(camera_ray.direction_, c2w);
	camera_ray.direction_ = subtract(&(camera_ray.direction_),
									&(camera_ray.origin_));
	camera_ray.direction_ = normalize(&(camera_ray.direction_));
	return (camera_ray);
}

/*
** select camera in list
*/

t_c		*get_camera(t_rt *rt_info)
{
	t_c *camera;

	camera = NULL;
	if (rt_info->count_->c_)
	{
		camera = rt_info->lst_pos.cur_c->content;
		rt_info->lst_pos.cur_c = rt_info->lst_pos.cur_c->next;
	}
	return (camera);
}

