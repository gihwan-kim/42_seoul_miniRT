/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:44:12 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/30 15:05:31 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

// if ray not intersact to object pixel color is 0
// 픽셀 중심에서 점의 위치를 계산 하려면 원래 래스터 공간으로 표현된 픽셀 좌표를 변환해야한다.(월드공간으로)
// world space : object, light, camera 가 모두 표현되는 공간
// t : ray origin 과 ray 가 만나는점 간의 거리
static int	shader(t_rt *rt_info, t_ray *camera_ray)
{
	double	t;
	double	c;

	t = t_infinity;
	if (intersection_controller(rt_info, camera_ray, &t))
	{
		return (pixel_shader(rt_info, camera_ray, &t));
	}
	else
	{
		// background color
		return (0);
	}
}

int			make_img(t_rt *rt_info, int width, int height)
{
	t_matrix	cam_to_wrold;
	t_ray		camera_ray;
	t_c			*camera;
	int			h;
	int			w;
	t_ray		test;
	h = -1;
	if(!(camera = get_camera(rt_info)))
		return (ERROR);
	cam_to_wrold = lookat(camera);
	// printf("cam_to_world\n");
	// print_matrix(&cam_to_wrold);
	// test = make_camera_ray(500, 500, &cam_to_wrold, rt_info, camera);
	// pr
	
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
		if (h == height/4)
			return (SUCCESS);
	}
	return (SUCCESS);
}
