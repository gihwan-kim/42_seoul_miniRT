/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:44:12 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/21 15:15:30 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

int		shader(t_rt *rt_info, t_ray &camera_ray)
{
	t_vec	camera_ray;
	// if ray not intersact to object pixel color is 0
	// 픽셀 중심에서 점의 위치를 계산 하려면 원래 래스터 공간으로 표현된 픽셀 좌표를 변환해야한다.(월드공간으로)
	// world space : object, light, camera 가 모두 표현되는 공간
	if (check_intersact())
		return (pixel_shader(rt_info));
	else
		return (0);
}

int	make_img(t_rt *rt_info, int width, int height)
{
	t_matrix	cameraToWorld;
	t_ray		camera_ray;
	t_c			*camera;
	int			h;
	int			w;

	h = -1;
	if(!(camera = get_camera(rt_info)))
		return (ERROR);
	cameraToWorld = lookAt(camera);
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			camera_ray = make_camera_ray(w, h, &cameraToWorld, rt_info, camera);
			rt_info->img_.data[h * width + w] = shader(rt_info, &camera_ray);
		}
	}
	mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr, 
		rt_info->img_.img_ptr, 0, 0);
	mlx_loop(rt_info->mlx_ptr);
}
