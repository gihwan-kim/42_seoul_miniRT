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

				#### sphere
			
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

					3. ray 가 구와 만나는지 계산
						https://en.wikipedia.org/wiki/Loss_of_significance
						https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
						부동 소수점인 수로 연산을 할 경우애서
						b 와 판별식의 근의 부호가 동일한 부호를 가지지 않지만 값은 서로 비슷할때
						유효숫자를 올바르게 알 수 없을 수도 있다. 값이 잘릴 수도 있다.
						x - y = 0.1234567891234567890 − 0.1234567890000000000
						실제 답		:   0.0000000001234567890
						손실 발생	: 	0.1234567891 − 0.1234567890 = 0.0000000001
									(유효숫자가 1개인 것처럼 보인다. 실제로는 10개인데...)

						2 번 에서 구한 것들을 활용하여 근의 공식을 통해 확인하면 된다.

					4. 여러개의 object 를 통과하는 ray
						https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/minimal-ray-tracer-rendering-spheres
						교차점에서 rayorigin 까지의 거리가 가장 짧은 것(= t)을 구한다.
				 
				 ### plane
					ray :  l_0 + l * t = P

					p	: plane 과 만나는 점
					l_0 : ray origin
					l	: ray direction

					palen 의 성질 : (p - p_0) ● n = 0
					-> vector pp_0 는 plane 의 normal vector 와 직교하므로 내적은 0 이다.
					p_0	: 좌표계에서 palne 까지의 거리를 계산할 수 있는 점
					n	: palne 의 normal vector, plane 과 직교하는 vector 

					ray 와 plane 이 교차한다면 교점은 ray 와 plane 이 한 점을 공유하게된다.
					위 2개 으 공식을 통해 ray 와 plane 의 교점인 p 를 구할 수 있다.
					
					p = l_0 + l * t  ----(a)
					(p - p_0) ● n = 0 ----(b)

					a 를 b 에 대입
					(l_0 + l * t - p_0) ● n = 0
					t 에 대하여 정리
					t = (p_0 - l_0) ● n / (l ● n)

					ray 와 plane 이 같은 평행할 경우 : 근이 무한개 또는 교차하지 않음
					l ● n 이 0 에 수렴할 경우 t 값이 무한대로 나옴 -> 에러 처리
					t 가 양수 이어야 하므로 
				
				### triangle
					https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/why-are-triangles-useful
					복잡한 object 를 표현할떄 삼각형을 사용하기도 한다.
					polygonal meshe 나 NURBS 의 표면과 ray 의 교차를 확인하는 것은 매우 복잡하고 느리다.
					반면에 삼각형과 ray 가 교차하는 것은 간단하고 최적화 하기도 편하다.
					NURBS 나 Bezier patches 와 같은 복잡한 obejct 들을 triangle mesh 들로 변환하여 계산할 수 있다.
						! NURBS
							Non-Uniform Rational B-Splines: 비균일 유리 B스플라인
							단순한 2D 선, 원, 호, 커브에서 가장 복잡한 3D의 유기적 자유 형상 서피스 또는 솔리드에 이르기까지,
							어떠한 형태도 정확하게 표현할 수 있는 수학적 표현 방법입니다.
					
					1. 삼각형에 대한 정보
						1-1 삼각형은 3개의 정점, 점으로 정의된다. (정점 - 꼭짓점)
						1-2 3차원 상에서 정의되어있다.
						1-3 삼각형은 동일 평면에 있다.
					
					2. Ray-Triangle Intersection: Geometric Solution
						https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
						2-1. ray 와 삼각형(a,b,c)이 이루는 평면이 만나는 점(p-phit) 구하기
							ax + by + cz + d = 0 과 p = O + tR 을 연립하여 t 에대한 식으로 정리
							ray 와 triangle 이 만나는 점 p 찾기
							ray 의 매개변수 방정식 : p = O + tR 
							(R : ray direction, O : ray origin, t : O 와 P 사이의 거리)

							※ ray 와 trinangle 이 평행할 경우
								intersect 가 아니다.
								triangle 의 법선벡터(normal vec) 와 ray 가 서로 수직으로 만나야한다.
							※ triange 이 ray 뒤에 있는 경우
								t < 0 일 경우 ray oingin 뒤에 있기 때문에 화면에 보이지 않는다.
						2-2. ac x ap, ab x ap 의 방향이 반대이어야한다.
								두 결과를 내적하면 음수가 되어야한다.
								이와같이 3점을 모두 구해서 확인한다.
				### square
						square 가 있는 평면과 만나는 점 : P
						1. 같은 평면에 있는지 확인
						2. p 가 정사각형안에 포함되는지 확인한다.
							|sq_origin - p| > 정사각형의 한 변의 길이 / 2
							정사각형의 중심점에서 p 까지의 벡터를 구한다. 이 벡터가 원점에 있다고 생각하면
							방향벡터 sq_origin - p 의 각 점 x, y, z마다 정사각형의 한변의 길이 / 2 보다 큰지 확인을 한다.
							크다면 p 가 정사각형 밖에 있음을 알 수 있다. 모든점이 정사각형의 한변의 길이 / 2 보다 작아야한다.

				###	cylinder
					원기둥의 중심을 지나는 직선이 중심 축이된다.
					p_a : 아마 원점인듯?
					중심 축 : P_a + V_a * t
					반지름이 r 인 원기둥의 방정식
					: (q - p_a - (v_a ● (q - p_a))v_a)^2 - r^2 = 0
					q = (x, y, z) : 원기둥의 한 점
					ray : p + vt = q
					
					< 원기둥이 무한할 경우 >
					ray 와 원기둥의 방정식이 만나는 점인 q 에 ray 방정식을 대입하여
					ax^2 + bx + c = 0
					a = (v - (v ● v_a)v_a)^2
					b = 2(v - (v ● v_a)v_a) ● (Δp - (Δp ● v_a)v_a)
					c = (Δp - (Δp ● v_a)v_a)^2 - r^2
					Δp = p - p_a


					< 뚜껑이 있는 원기둥 >
					윗 뚜껑 중점 	: p_1
					아래 뚜껑 중점	: p_2
					반지름이		: r
					p_a = p_1
					v_a = (p_2 - p_1) / |p_2 - p_1|

					(q - p_a - (v_a ● (q - p_a))v_a)^2 - r^2 = 0
					(v_a ● (q - q_1)) > 0
					(v_a ● (q - q_2)) < 0

					1. at^2 + bt + c = 0 로 부터 t_1 과 t_2 를 찾는다.
					2. t1, t2 가 존재한다면 음수가 아니거나 
						q = p + v t 인  q 에서
						(v_a ● (q - q_1)) > 0 이고
						(v_a ● (q - q_2)) < 0 인 것을 찾는다.
					3. 아래, 윗 뚜껑과 각각 만나는 점을 계산한다. --> 현 과제는 뚜껑이 없다.
						만약 존재한다면 음수가 아니거나
						(v_a ● (q - q_1)) < r^2 인 것을 찾는다
					4. 2,3 에서 찾은 것들 중 가장 작은 것을 찾는다.


					
		2 그 외의 obejct
	
3. shading
	ray 가 object 와 만나는지 확인이 되면 color 값을 찾아야한다.
	3-1 얼마나 많은 빛이 물체에 비치는지
	3-2 빛의 방향
	3-3 물체 자체의 특성, 색깔
	3-3 카메라의 방향 : 반사광의 양은 카메라의 방향에 따라 다르다.

	# secondary rays
	https://www.scratchapixel.com/lessons/3d-basic-rendering/rendering-3d-scene-overview/introduction-light-transport
		눈으로 부터 나오는 primary ray 를 쏘았을때 어떤 면에 ray 가 만나는 점을 P 라하자.
		이때 두가지를 계산해야한다.
			1. direct lighting (직접광)
				p 에 light source 로 부터 얼마나 많은 빛이 오는지 
				1-1 shadow ray
					p 에서부터 light source 까지 를 직선으로 이었을때
					p 에서 light 까지 가는 도중 다른 object 를 만날 경우
					p 는 그림자이다.
			2. indirect lighting (간접광)
				(간접광 - 다른 물체의 표면으로 부터 반사된 빛)
				p 에 간접적으로 오는 빛이 얼마나 되는지 
				p 를 시작으로하는 secondary ray 라는 새로운 ray 를 만들어 확인한다.
				secondary ray 가 다른 물체와 만난다면 만나는 지점의 직접광, 간접광을 계산해야하고
				계산된 빛의 을 다시 p 에 주어야한다.
				--> 이 과정을 재귀로 구현
				: secondary ray 가 표면에 닿을때마다 direct lighting 과 indirect lighting 을 계산한다.
					몇 번 정도 충돌시킬 것인지 정해야함 아니면 계속 무한대로 충돌
					빛이 반사될때마다 빛의 에너지는 계속 떨어진다.
					
					->> unidirectional path tracing 알고리즘이라 부른다.
						: camera 에서 light source 까지의 하나의 방향만 가지고 있다.
		※ shading
			shading 이란 무엇인가
			object 의 외형에 영향을 미치는 것들은 어떤것이 있을까?
			(Ex. 
				light intensity,
				direction,
				the orientation of the surface of objects,
				color of object)
		https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading
			렌더링 과정은 2가지 단계로 나눌 수 있다.
			 	1. visibility
				 	rasterization 또는 ray-tracing 을 사용하여 구현
				2. shading

			1. shading 이란?
				3D 에서 객체의 색상을 계산하는 과정
				visibility 에서 물체가 보이는지 확인을 한다면
				shading 에서는 주어진 관점(viewpoint)에서 볼 떄 객체의 색상을 계산하거나
				시뮬레이션 하는 것을 처리한다.

			2. 용어 설정
				photorealistic rendering (사실적 렌더링) 에서 표현하려는 object 의 외형은
				lighting 과 물체의 속성에 따라 결정된다.
				물체의 속성 : 물체의 방향, 물체의 색깔

				direct lighting 	: object 에 반사된 빛이 눈에 들어온 것
				indirect lighting 	: object 에 반사된 빛이 다른 물체에 반사되서 눈에 들어간것

			3. 빛과 물체의 상호작용 및 shading 의 필수 요소 : N P L V
				우리가 보는 물체는 물체 자치를 보는 것이 아닌 물체의 표면에 반사된 빛을
				보는 것이다.
				빛은 에너지이다.
				물체의 방향은 빛의 양에 많은 영향을 미친다.
				광원을 향해 물체를 이동시킬 경우 밝아지거나 어두워질 것이다.
				물체의 방향(normal)을 바꾸는 것은 광원의 위치를 바꾸는 것과 같은 효과이다.

				N : surface orientation, 물체 표면의 법선벡터
				L : light direction
				P : ray 와 obejct 가 만나는 점
				V : viewing direction
				P: shaded point
				N: normal at P
				L: light direction
				V: view direction
				Angle of Incidence: the angle between N and L
				Angle of Reflection: the angle between the reflected ray and the normal
				표면의 종류 : mirror(shiny) or glossy, matte or diffuse

				glossy : 표면이 매끄럽지 않음, 반사된 ray 의 방향이 제각각, 굴곡들이 하나의 또 다른 거울처럼 반사됨
							흐릿하게 반사됨, 그림자가 번짐
				diffuse : light 가 물체안으로 들어가서 안에서 복잡하게 튕겨지며 물체를 벗어난다.
							물체를 벗어나면 incident direction (다른 물체로부터 반사된 빛) 이된다.
							ray 가 들어온 개수만큼 반사되지 않는다. 물체 안에서 개수가 줄어듦. 방향또한 랜덤
							따라서 diffuse object 는 모든 방향으로 입사광을 동일하게 반사한다고 생각한다.
							따라서 보는 방향이 바뀌더라도 색은 같다.
				
				ray 가 눈으로 들어가야만 물체를 보는 것이다!
				ray 가 눈에 닿지 않으면 안보이는 것으로 간주한다.

				reflaction 과 glossy reflaction 는 보기에 따라 다르다. 화각에 따라다름
				
				diffuse reflaction 은 독립적이다. 어떤 각도에서든지 밝기는 바뀌지 않는다. diffuse 물질은
				모든 방향으로 입사광을 동일하게 반사하기때문이다.

				# 물체가 색을 가지는 이유
					백생광 : 모든 스팩트럼의 색을 가지고 있음.

					white light(백색광)이 물체에 부딪히면 백색광의 몇몇 색은 물체에 흡수되고 나머지 색은 반사된다.
					물체에 흡수된 색들은 물체가 가진 고유의 색과 동일하다.
					Ex.
						오렌지는 오렌지 색인데 파란색을 대부분 흡수하고 빨간색과 초록색은 반사되어 섞이면서 오렌지색이
						된다. RGB 색 별로 흡수하는 양이 다르기 때문에 오렌지 색으로 보이는 것

					흡수되지 않은 빛들이 반사된다.
					
					! 어떻게 물체의 색을 알아내지?
						물체의 색은 물체가 diffuse 일때만 알 수 있다.

					일반적으로 대부분의 물체는 diffuse 와 glossy 속성 모두 어느정도는 가지고 있다.
					Ex. 
						오렌지는 거의 diffuse 이지만 매우 얇게 거울처럼 작용(mirror)하는 매우 얇은 층이 덮여 있어
						색은 가지고 있지만 조금 반짝거린다.

					물체의 색은 입사광의 양에대한 반사광의 비율로 정의된다.
