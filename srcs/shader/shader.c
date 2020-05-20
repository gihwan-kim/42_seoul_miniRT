/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:44:12 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/20 15:41:16 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

< ray-tracing 과 rasterization >

ray-tracing : image 중심적

rasterization : object 중심적
	ray tracing 에 비해 object 가 보이는지 보이지 않는지 판단하기 쉽다.
	shading 작업이 ray tracing 에 비해 좋지 않다.

< ray tracing >

## ray tracing 의 3단계
3 가지 단게로 나눌 수 있다.

1. Casting Rays
: cast a ray for each pixel in the image

2. ay-Geometry Intersection: 
test if a ray intersects any of the objects in the scene 
(this requires to loop over all the objects for each cast ray).

3. Shading
: find out what the object "looks like" at the intersection point between t
he ray and the object (if an intersection has occurred).


1. casting ray into the scene
	각 픽셀당 ray 를 쏴줘야 한다. 이 ray 를 camera ray primary ray 라고 한다.
	1-1 camera ray or primary ray
		시각적인 문제를 해결하는데 사용한다. (ray casting)
		pixel 을 향해 ray 를 쏜것
		origin : ray 의 원점
		direction : 방향(normalized)

		camera 의 원점이 (0,0,0) 인것을 기준으로한다.


		t : t 의 값에 따라 ray 의 방향이 결정된다.
			음수 : origin 뒤로 ray 가 나아감
			양수 : origin 앞으로

		1. camera ray (the first rays cast into the scene which have for origin the origin of the camera)
			ray 가 object 와 intersect 한지 확인한다.
				intersect - t 를 반환한다. intersection 지점과 origin 간의 거리를 계산하고 그것(t)을 반환한다.
				intersect : O
					(hitpoint) =  origin + t * direction
		2. second ray (shadow, diffuse, specular, transmission)

		※ generating camera Rays

			renderer 의 목적 : 각 pixel 에 색을 할당하는 것, 3d 화면을 보는 것처럼 보여야한다.
			image 를 생성한다는 것은 primary ray(= camera ray)를 생성한다는 것.
			camera ray : camera 의 origin 에서 뻗어나온다. 
				방향   : camera 원점 -> pixel 한개
			* primary ray 만들기
			카메라의 원점에서 각 픽셀의 중심을 지나는 직선이라 생각하면 된다.
			primary ray 의 원점은 camera 의 원점이고
			primary ray 의 방향은 camera 의 원점에서 pixel 의 중심이다.
			pixel 의 중심을 계산하기 위해서는 pixel 좌표(왼쪽 상단이 (0,0)인 rater space 로 표현되어 있음)를
			world space 로 변환시켜야한다.
			image 는 world space 의 원점에서 z 축에 넣여있고 1 unit 만큼 떨어져 있다고 정해놓는다.
			world space 에서의 pixel 좌표와 raster space 의 pixel 의 좌표의 관계를 찾아야한다.
			
			1. 현재 pixel 의 위치를 normalize 시켜야한다. 
				: normalized 된 공간을 NDC space(= Normalized Device Coordinates) 라 한다.
				! rasterization 의 NDC space 와 다르다.

				pixel_ndc_x = (pixel_x + 0.5) / image_width
				pixel_ndc_y = (pixel_y + 0.5) / image_height
				(0.5 를 더한 것은 pixel 의 가운데를 통과시켜야하기 때문)

				NDC space 로 변환되면 x, y 값은 [0,1] 의 범위를 가지게 된다.
				
	
2. Testing for Ray-Geometry Intersections
	object 의 모양에 따라 다르다.
	2-1 수학적으로 표현될 수  있는 obejct
		(https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes)
	2-2 그 외의 obejct
		작은 삼각형 매쉬로 세분화 시켜야한다.
	2-3 Intersections function

3. shading
	ray 가 object 와 만나는지 확인이 되면 color 값을 찾아야한다.

	3-1 얼마나 많은 빛이 물체에 비치는지
	3-2 빛의 방향
	3-3 물체 자체의 특성, 색깔
	3-3 카메라의 방향 : 반사광의 양은 카메라의 방향에 따라 다르다.


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
	// cameraToWorld = multiply_by_matrix(new_vector(0, 0, 0), )
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			// generate primary ray
			// check intersection in shader
			rt_info->img_.data[h * width + w] = shader(rt_info);
		}
	}
	mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr,
		rt_info->img_.img_ptr, 0, 0);
	mlx_loop(rt_info->mlx_ptr);
}
