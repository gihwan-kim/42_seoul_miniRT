방향 벡터 : 보통 크기가 1인 방향을 나타내는 벡터이다.

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

2. ray-Geometry Intersection: 
test if a ray intersects any of the objects in the scene 
(this requires to loop over all the objects for each cast ray).

3. Shading
: find out what the object "looks like" at the intersection point between t
he ray and the object (if an intersection has occurred).


##1. casting ray into the scene
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
				광선의 원점을 카메라의 원점(O : 0,0,0)으로 정하고 광선의 방향을 OP 로 정의하여 normalize 하면
				픽셀을 지나는 ray 의 방향을 구할 수 있다.

				float imageAspectRatio = imageWidth / (float)imageHeight; // assuming width > height 
				float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio; 
				float Py = (1 - 2 * ((y + 0.5) / imageHeight) * tan(fov / 2 * M_PI / 180); 
				Vec3f rayOrigin(0); 
				//Vec3f(Px, Py, -1) 를 의미할 뿐 아직 ray 의 방향이 아니다. normalzie 해야한다.
				Vec3f rayDirection = Vec3f(Px, Py, -1) - rayOrigin; 
				// normalize 를 해주어야 방향벡터가 된다.!
				rayDirection = normalize(rayDirection); 
			
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
				// cameraToWolrd 행렬을 픽셀과 카메라의 위치에 곱해주어 world space 로 옮겨준다.
				//rayOrigin 벡터에 cameraToWorld 행렬을 곱한결과를 rayOriginWorld 에 넣는다.
				cameraToWorld.multVectMatrix(rayOrigin, rayOriginWorld); 
				// 픽셀을 좌표계로 변환한 점(px,py,-1) 에 cmaeraToWorld 행렬을 곱한 결과를 rayPWorld 에 넣는다.
				cameraToWorld.multVectMatrix(Vec3f(Px, Py, -1), rayPWorld); 
				Vec3f rayDirection = rayPWorld - rayOriginWorld; 
				rayDirection.normalize(); // it's a direction so don't forget to normalize 
		
			※ lookAt function
				1. lookAt function 을 사용하는 이유
					cameraToWorld matrix 와 같은 4x4 행렬을 이용해 camera 를 이동시킬 경우
					camera 는 원점에 놓이고 음의 z 축에 따라 정렬되어있음을 전제로한다.
					하지만 4x4 행렬을 사용하여 camera 의 위치를 조정하는 것이 친숙하지 않을 수도 있다.
					(maya 와 blender 프로그램을 사용하지 않는한 불편할 수 있다.)
					https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
				
				2. 카메라의 위치와 방향을 구하기위해 필요한 것
					카메라 위치를 설정히는 점(from - vector), 카메라가 바라보는 점(to - vector)
				
				3. method 
					matrix 모양 : row major
					좌표 시스템  : 오른손 좌표계
					카메라 기준 좌표계 용어
						right	 	: x 축과 비슷
						up			: y 축과 비슷
						forward		: z 축과 비슷

						Right_x 	Right_y		Right_z		0
						Up_x		Up_y		Up_z		0
						Forward_x	Forward_y	Forward_z	0
						from_x		from_y		from_z		1
					
					3-1 forward 축 계산

						normalize(form - to)

					3-2 right 계산
						random (0, 1, 0) // 임시 up- y 축 역할

						cross_product(random, forward)

					3-3 up 계산
						cross_product(forward, right)
					
					3-4 matrix 에 값 넣기

	

## 2. Testing for Ray-Geometry Intersections
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