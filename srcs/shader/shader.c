/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:44:12 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 19:49:25 by gihwan-kim       ###   ########.fr       */
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

// if ray not intersact to object pixel color is 0
// 픽셀 중심에서 점의 위치를 계산 하려면 원래 래스터 공간으로 표현된 픽셀 좌표를 변환해야한다.(월드공간으로)
// world space : object, light, camera 가 모두 표현되는 공간
// t : ray origin 과 ray 가 만나는점 간의 거리
static int	shader(t_rt *rt_info, t_ray *camera_ray)
{
	t_phit	h_obj_info;
	double	t;
	int		color;

	h_obj_info.type = 0;
	h_obj_info.obj = NULL;
	if (intersection_controller(rt_info, camera_ray, &h_obj_info, &t))
	{
		h_obj_info.colorf = get_h_obj_color(&h_obj_info);
		color = pixel_shader(rt_info, camera_ray, &t, &h_obj_info);
		return (color);
	}
	else
		return (0);
}

int			make_img(t_rt *rt_info, t_c *camera, int width, int height)
{
	t_matrix	cam_to_wrold;
	t_ray		camera_ray;
	int			h;
	int			w;

	h = -1;
	cam_to_wrold = lookat(camera);
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			camera_ray = make_camera_ray(w, h, &cam_to_wrold, rt_info, camera);
			rt_info->img_.data[h * width + w] = shader(rt_info, &camera_ray);
		}
	}
	return (SUCCESS);
}
