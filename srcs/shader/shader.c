/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:44:12 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/11 20:12:26 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

static t_rgb_f	get_h_obj_color(t_phit *h_obj_info)
{
	t_e_obj type;
	t_rgb_f	result;

	type = h_obj_info->type;
	if (type == sphere)
		result = get_sphere_color((t_sp*)(h_obj_info->obj));
	else if (type == square)
		result = get_square_color((t_sq*)(h_obj_info->obj));
	else if (type == cylinder)
		result = get_cylinder_color((t_cy*)(h_obj_info->obj));
	else if (type == triangle)
		result = get_triangle_color((t_tr*)(h_obj_info->obj));
	else
		result = get_plane_color((t_pl*)(h_obj_info->obj));
	return (result);
}

/*
** color : color of (x,y) pixel
** t : distance between ray origin and hitpoint
*/

static t_rgb	shader(int w, int h, t_rt *rt_info, t_matrix *cam_to_world)
{
	t_phit	h_obj_info;
	t_ray	camera_ray;
	double	t;
	t_rgb	color;

	h_obj_info.type = 0;
	h_obj_info.obj = NULL;
	camera_ray = make_camera_ray(w, h, cam_to_world, rt_info);
	color.r_ = 0;
	color.g_ = 0;
	color.b_ = 0;
	if (intersection_controller(rt_info, &camera_ray, &h_obj_info, &t))
	{
		h_obj_info.colorf = get_h_obj_color(&h_obj_info);
		color = pixel_shader(rt_info, &camera_ray, &t, &h_obj_info);
	}
	return (color);
}

int				make_img(t_rt *rt_info, t_c *camera, int width, int height)
{
	t_matrix	cam_to_world;
	t_rgb		color;
	t_rgb		**bmp_data;
	int			h;
	int			w;

	h = -1;
	bmp_data = create_bmp(width, height);
	cam_to_world = lookat(camera);
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			color = shader(w, h, rt_info, &cam_to_world);
			rt_info->img_.data[h * width + w] = (65536 * color.r_)
												+ (256 * color.g_) + color.b_;
			if (rt_info->save)
				bmp_data[h][w] = color;
		}
	}
	if (rt_info->save)
		bmp(width, height, bmp_data);
	return (SUCCESS);
}
