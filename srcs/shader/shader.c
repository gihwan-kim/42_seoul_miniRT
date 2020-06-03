/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:44:12 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/03 16:58:32 by gihwan-kim       ###   ########.fr       */
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
	// else if (type == plane)
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
	// t_rgb_f ambient_color;
	double	t;
	int		color;

	t = t_infinity;
	if (intersection_controller(rt_info, camera_ray, &h_obj_info, &t))
	{
		// multi_colorf(&ambient_color, rt_info->t_a_->light_);
		h_obj_info.colorf = get_h_obj_color(&h_obj_info);
		// write(1, "obj check\n", 11);
		// ambient_color = colorf_multi_colorf(&ambient_color, &(h_obj_info.colorf));
		color = pixel_shader(rt_info, camera_ray, &t, &h_obj_info);
		// printf("final : %d\n", color);
		return (color);
		// return (200);
	}
	else// background color
		return (0);
}

int			make_img(t_rt *rt_info, int width, int height)
{
	t_matrix	cam_to_wrold;
	t_ray		camera_ray;
	t_c			*camera;
	int			h;
	int			w;

	h = -1;
	if(!(camera = get_camera(rt_info)))
		return (ERROR);
	cam_to_wrold = lookat(camera);
	// printf("cam_to_world\n");
	// print_matrix(&cam_to_wrold);
	// test = make_camera_ray(500, 500, &cam_to_wrold, rt_info, camera);
	// pr
	// printf("height: %d\t widht: %d\n", height, width);
	// height = 10;
	// width = 15;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			camera_ray = make_camera_ray(w, h, &cam_to_wrold, rt_info, camera);
			// printf("ray direction\n");
			// print_vec(&(camera_ray.direction_));
			// printf("ray origin\n");
			// print_vec(&(camera_ray.origin_));
			rt_info->img_.data[h * width + w] = shader(rt_info, &camera_ray);
			// printf("now color : %d\n", rt_info->img_.data[h * width + w]);
		}
		// if (h == height/4)
		// 	return (SUCCESS);
	}
	return (SUCCESS);
}
