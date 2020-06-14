# 42_seoul_miniRT
This project is libft project in 42 seoul course

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
