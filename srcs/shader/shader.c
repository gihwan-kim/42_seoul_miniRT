/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:44:12 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/19 17:50:48 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

int		shader(t_rt *rt_info)
{
	// 카메라의 기본 위치는 원점(0,0,0) 으로 고정된다.
	t_vec	camera_ray;
	// 필름 면은 카메라 원점에서 1 unit 만큼 떨어진 곳에 있다.
	// if ray not intersact to object pixel color is 0
	// 픽셀 중심에서 점의 위치를 계산 하려면 원래 래스터 공간으로 표현된 픽셀 좌표를 변환해야한다.(월드공간으로)
	// world space : object, light, camera 가 모두 표현되는 공간
	if (check_intersact())
		return (pixel_shader(rt_info));
	else
		return (0);
}

void	camer_to_world()
{
	t_vec tmp;

	ft_bzero(&tmp, sizeof(t_vec));
	
}

int	make_img(t_rt *rt_info)
{
	t_matrix	cameraToWorld;
	int			width;
	int			height;
	int			h;
	int			w;

	width = rt_info->t_r_->size_x_;
	height = rt_info->t_r_->size_y_;
	h = -1;
	// 디스플레이 연결
	rt_info->img_.img_ptr = mlx_new_image(rt_info->mlx_ptr, width, height);
	rt_info->img_.data = (int *)mlx_get_data_addr(rt_info->img_.img_ptr,
		&rt_info->img_.bpp, &rt_info->img_.size_l, &rt_info->img_.endian);
	cameraToWorld = multiply_by_matrix(new_vector(0, 0, 0), )
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			rt_info->img_.data[h * width + w] = shader(rt_info);
		}
	}
	mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr,
		rt_info->img_.img_ptr, 0, 0);
	mlx_loop(rt_info->mlx_ptr);
}
