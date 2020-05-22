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
	https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes
	> object 의 모양에 따라 다르다.>
		1 수학적으로 표현될 수  있는 obejct
			### object 의 모양을 표현하는 두가지 방법
					1. Parametric Surfaces
					매개변수 방정식의 형태
					곡선, 선을 표현하기 위해서는 1개의 매개변수
					3d 면을 표현하기 위해서는 2개의 매개변수가 필요
				f(x, y) = z
				2. Implicit Surfaces
					parametic surfaces 와 비슷하다.
					P(x, y) = 0
					P(x, y, z) = 0
					#### Implicit Surfaces 를 사용하는 이유
						다른 geometry type 을 사용하는 것 보다 간단함
						빠르다
						모양이 간단하기 때문에 복잡한 object 를 표현하기 쉽다.
			### bounding volume
				구를 bounding volume 은 수학적으로 표현하기 힘든 object 를
				감싸는 구로 사용하는 것이다.
				ray 가 object 를 감싸는 구를 지난다면 object 가 지나는지 확인하는 방식으로
				진행을 하면 좀더 효율적이다.

			### parametric 또는 implicit surfaces	의 장점
				이러한 surfcae 의 모양을 결정하는 방정식들은 surface 에 주어전 한 점의
				derivatives, bi-tangent, tangent, normal vector 를 계산하는데 유용하다.
				derivatives : 텍스처 필터링에 사용
				bi-tangent, Tangent : shading 에서 object 의 한점의 로컬 좌표계에 사용된다.

			### production renderers 들과 이번 과제의 render 의 차이점
				대부분의 renderer 들은 object 들의 모양을 구현하여 ray 교차를 확인하는 것이아닌
				polygon mesh 를 사용하여 확인한다.
				하지만 이번에 수행할 miniRT 과제는 polygon mesh 를 사용하지 않고 옛날 방식으로 구현한다.

			!!! 이번에 구현할 과제 miniRT 는 polygon mesh 를 사용하지 않는 옛날 방식으로 구현했다 !!!

			### Geometric Solution : ray-sphere intersection
				ray 가 구에 교차하는 점 p0 p1 를 찾아야한다
				ray 의 시작점 O 에서 p0 까지의 거리 : t0
				ray 의 시작점 O 에서 p1 까지의 거리 : t1

				ray 는 매개변수 형태로 O + tD 로 표현할 수 있다.
				( O : ray 시작점, D : ray 방향벡터)
				t 값을 변경해가며 p0, p1 을 찾아야한다.
				t < 0 : p0 과 p1 이  O 뒤(ray 의 방향 반대)에 있다.
				t > 0 : p0 과 p1 이  O 앞(ray 의 방향)에 있다.
				t = 0 : p0 과 p1 이  O 에 있다.

			### Analytic Solution
			
				1. 구의 중심이 원점일 경우
					구의 방정식 : x^2 + y ^2 + z^2 = R^2
					x,y,z 가 cartesian coordinate (직교 좌표계)일때 x,y,z 를 간단하게
					P^2 - R^2 = 0 으로 표현할 수있다.
					(P : x,y,z 가 점 P의 좌표라고 생각한다.)
					P^2 - R^2 = 0 방정식은 구를 implicit function 형태로 표현한 것이다.
					Implicit 형태들을 polygon 들이 연결되어있는 모양으로 정의할 수도 있지만
					방정식의 형태로 보면 함수의 형태로 정의될 수도 있다.
					
					ray 가 구에 만나기 떄문에 아래와 같이 표현할 수 있다.
					|O + tD|^2 - R^2 = 0

					O^2 + (Dt)^2 + 2ODt − R^2
					=  D^2t^2 + 2ODt + O^2 - R^2

					2차 방정식의 형태로 보인다
					f(X) = aX^2 + bX + c
					
					a = D^2
					b = 2OD
					c = O^2 - R^2
					x = t)

					x = 근의 공식
					Δ = b^2 − 4ac (근의 공식에서 루트안의 부분)

					t0 = t1: ray 가 원에 접한다.(한점에서 만난다.)
					t0 > 0, t1 > 0 : ray 가 구에 두점에서 만난다.
					t0 < 0, t1 > 0 : ray 의 원점이 구 안에 있다.
					t0 < 0, t1 < 0 : ray 의 방향벡터 반대방향에 구가 있다고.
					t0, t1 이 없다  : 교차하지 않는다.
					t0 > 0, t1 < 0 : 불가능 t0 은 항상 t1 보다 작거나 같다.
				
				2. 구의 중심이 원점이 아닐 경우
					O : ray 의 origin
					C : sphere 의 위치
					D : ray 의 방향
					|P - C|^2 - R^2 = 0   (원점에서 각 좌표별로 C 만큼 이동한 위치에 존재)
					방정식 1 : |O + tD - C|^2 - R^2 = 0
					방정식 1 을 풀면

					D^2 * t^2 + 2D(O - C)t + |O - c|^2 - R^2 = 0
					( D 는 normalize 이므로 D^2 = 1 이기떄문에 t^2 의 계수는 1)

					f(X) = aX^2 + bX + c 꼴로 정리하면

					a = 1
					b = 2D(O − C)
					c = |O − C|^2 − R^2

					구와 만나는 점	: Phit
					Phit 를 정규화	: Nphit
					구의 중심		: C

					Phit = ray_origin + ray_direction * t (t는 t0 이다. t1 아님)
					Nhit = normalize(Phit - C)

				3. ray 가 구와 접하는지 계산
					https://en.wikipedia.org/wiki/Loss_of_significance
					https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
					부동 소수점인 수로 연산을 할 경우애서
					b 와 판별식의 근의 부호가 동일한 부호를 가지지 않지만 값은 서로 비슷할때
					유효숫자를 올바르게 알 수 없을 수도 있다. 값이 잘릴 수도 있다.
					x - y = 0.1234567891234567890 − 0.1234567890000000000
					실제 답		:   0.0000000001234567890
					손실 발생	: 	0.1234567891 − 0.1234567890 = 0.0000000001
								(유효숫자가 1개인 것처럼 보인다. 실제로는 10개인데...)
		2 그 외의 obejct
	

3. shading
	ray 가 object 와 만나는지 확인이 되면 color 값을 찾아야한다.

	3-1 얼마나 많은 빛이 물체에 비치는지
	3-2 빛의 방향
	3-3 물체 자체의 특성, 색깔
	3-3 카메라의 방향 : 반사광의 양은 카메라의 방향에 따라 다르다.