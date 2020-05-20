/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:44:12 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/20 17:48:20 by gihwan-kim       ###   ########.fr       */
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
		2. second ray (shadow, diffuse, specular, transmission) : shading 에서 처리

		※ generating camera Rays

			https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays?http://www.scratchapixel.com/lessons/3d-basic-rendering/3d-viewing-pinhole-camera/how-pinhole-camera-works-part-1?
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
			
			NDC space
			: normalized 된 공간을 NDC space(= Normalized Device Coordinates) 라 한다.
			! rasterization 의 NDC space 와 다르다.

			1. raseter space -> NDC space
				pixel_ndc_x = (pixel_x + 0.5) / image_width
				pixel_ndc_y = (pixel_y + 0.5) / image_height
				(0.5 를 더한 것은 pixel 의 가운데를 통과시켜야하기 때문)

			2. NDC sapce -> screen space
				NDC space 로 변환되면 x, y 값은 [0,1] 의 범위를 가지게 된다.
				NDC space 는 모두 양수로 되어있기 때문에 xy 축 처럼 음수 양수를 가지도록 변경해 주어야한다.
				(= NDC space 는 원점이 왼쪽 상단으로 되어있는데 이를 가운데 점을 기준으로하도록 바꿔주어야한다)

				pixel_screen_x = 2 * pixel_ndc_x - 1
				pixel_screen_y = 1 - 2 * pixel_ndc_y
			
			3. screen space -> wolrd space 
				image 의 비율이 1:1 이 아닐 경우 image aspect ratio 를 구해 맞춰주어야한다.
				( 좌표계는 비율이 동일하기 떄문)
				
				iamge_aspect_ratio = image_width / image_ height
				pixel_camera_x = pixel_screen_x * iamge_aspect_ratio
				pixel_camera_y = pixel_screen_y

			3. screen space -> wolrd space
				field of view 값에 따라 screen space 의 길이가 바뀔 수 있다.

				pixel_camera_x = pixel_screen_x * iamge_aspect_ratio * tan(fov/2)
				pixel_camera_y = pixel_screen_y * tan(fov/2)

				P - (pixel_camera_x, pixel_camera_y, -1) 
				(= P : 변환된 픽셀의 위치)
				광선의 원점을 카메라의 원점(O)으로 정하고 광선의 방향을 OP 로 정의하여 normalize 하면
				픽셀을 지나는 ray 의 방향을 구할 수 있다.

				float imageAspectRatio = imageWidth / (float)imageHeight; // assuming width > height 
				float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio; 
				float Py = (1 - 2 * ((y + 0.5) / imageHeight) * tan(fov / 2 * M_PI / 180); 
				Vec3f rayOrigin(0); 
				Vec3f rayDirection = Vec3f(Px, Py, -1) - rayOrigin; // note that this just equal to Vec3f(Px, Py, -1); 
				rayDirection = normalize(rayDirection); // it's a direction so don't forget to normalize 
			
			4. camera 위치 이동
				이떄까지 camera 의 위치가 원점일 경우로 계산을 했었다.
				원점이 아닌 다른 위치에 camera가 있을 경우 그 점으로 이동하는 행렬을 계산하여 변환시킬 수 있다.
				원점 -> camera point 로 이동시키는 행렬(c2w)을 만든다
				camera to world transform matrix (c2w) 를 사용한다.
				
				float imageAspectRatio = imageWidth / imageHeight; // assuming width > height 
				float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio; 
				float Py = (1 - 2 * ((y + 0.5) / imageHeight) * tan(fov / 2 * M_PI / 180); 
				Vec3f rayOrigin = Point3(0, 0, 0); 
				Matrix44f cameraToWorld; 
				cameraToWorld.set(...); // set matrix 
				Vec3f rayOriginWorld, rayPWorld; 
				cameraToWorld.multVectMatrix(rayOrigin, rayOriginWorld); 
				cameraToWorld.multVectMatrix(Vec3f(Px, Py, -1), rayPWorld); 
				Vec3f rayDirection = rayPWorld - rayOriginWorld; 
				rayDirection.normalize(); // it's a direction so don't forget to normalize 

	

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
