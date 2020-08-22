# 42_seoul_miniRT
This project is libft project in 42 seoul course.
레이트래이싱을 사용하여 사물의 색깔, 그림자를 렌더링해주는 프로그램입니다.
스크린에 출력해주는 라이브러리는 42 minlibx 라이브러리를 사용하였고 쉐이더 작업은 직접 구현해주었습니다.

**Turn in files**
	All your files

**Makefile**
	all, clean, fclean, re, bonus

**Arguments**                      
	a scene in format *.rt

**External functs.**
	• open, close, read, write,malloc, free, perror,strerror, exit
	• All functions of the math library (-lm man man 3 math)
	• All functions of the MinilibX

**Libft authorized**
	Yes

**Description**
	The goal of your program is to generate images
	using the Raytracing protocol. Those computer
	generated images will each represent a scene, as
	seen from a specific angle and position, defined
	by simple geometric objects, and each with its own
	lighting system.


# Ex

**scene01**
![scene01](https://user-images.githubusercontent.com/33623130/90954592-6e0dda00-e4b0-11ea-94dc-f164bac51a6f.JPG)

**scene03**
![scene03](https://user-images.githubusercontent.com/33623130/90954593-6f3f0700-e4b0-11ea-8521-06dc5d50cac9.JPG)

**sphere**
![sphere](https://user-images.githubusercontent.com/33623130/90954596-6f3f0700-e4b0-11ea-9252-d366d7348bdf.JPG)

**triangle**
![triangle](https://user-images.githubusercontent.com/33623130/90954597-6fd79d80-e4b0-11ea-8d15-985d45bb7a45.JPG)

**plane**
![plane](https://user-images.githubusercontent.com/33623130/90954598-70703400-e4b0-11ea-9cb6-eb7fd288549a.JPG)


> scene 01, 03 의 경우 https://github.com/nesvoboda/minirt 의 rt 파일을 사용하였습니다.

> In case of scene01 scene02. i used  https://github.com/nesvoboda/minirt  rt file.

# 구현 후 소감
 - 한달 반정도 동안 miniRT 만 붙들고 있었는데 개인적으로 진로를 결정하는데 큰 도움이 된 프로젝트이었던것 같다.
 - 컴퓨터 그래픽스, cg 에 대해 어릴적부터 관심이 엄청 많았는데 막연하기만한 이 꿈을 과제를 통해 구체적으로 구현해보면서 어떤식으로 나아갈지 확신이 생기게된 프로젝트인것 같다.

# todo list

### 5/22
	1. list 의 첫번째 node 를 가리키는 포인터 부분 구현
	2. sphere intersection 구현

### 5/23
	1. 여러 개의 object 를 만날떄 어떻게 판단할지 구현
	2. 나머지 object intersection 구현

### 5/24
	1. triangle, square 구현
	2. 여러 개의 object 를 만날떄 어떻게 판단할지 구현

### 5/25
	1. triangle, square 구현 보충
	2. shader 부분 코드 수정 및 여러 소스파일로 분할
	3. vector 파일 여러 소스파일로 분할

### 5/27
	1. cylinder 구현
	2. object 리스트에서 현재 검색할 리스트체크하는 함수 get_node 다시 수정
	3. pixel shader 구현 및 관련 기술 학습
	4. 실제 충돌 테스트 까지 구현한 부분 테스트 해보기
		파싱할때 ft_strncmp 함수 앞에 ! 를 안붙여서 에러처리됐음
		파라미터 개수 체크 부분 실수함
		
### 6/3
	1. window 에 색은 표현된다.
	2. intersect 부분이 잘안돌아가는것 같다.
	3. intersection 처리, shadow, specluar 부분을 다시 확인하자
