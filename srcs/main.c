/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 11:44:13 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/11 15:17:27 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
/**
#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int	deal_key(int key, void *param)
{
	ft_putchar('x');
	return (0);
}

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "hello mlx!");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void*)0);
	mlx_loop(mlx_ptr);
	return (0);
}
**/
/**
실행파일 arg1 arg2
arg1 : .rt file
	.rt file : a scene description file

	arg1 rule :
		◦ It will contain the window/rendered image size, which implies your miniRT
		must be able to render in any positive size.
		1. 양의 크기를 가지는 image

		◦ Each type of element can be separated by one or more line break(s).
		2. 각 요소는 1개이상으 line break(s) 로 나뉘어져있다.

		◦ Each type of information from an element can be separated by one or more
		space(s).
		3. 하나의 요소로부터 각 type 의 정보는 1개 이상의 공백으로 나뉘어져 있다.

		◦ Each type of element can be set in any order in the file.
		4. 각 요소의 type 은 fil 에서 순서 없이 나열됨

		◦ Elements which are defined by a capital letter can only be declared once in
		the scene.
		5. 각 요소는 대문자로 각 장면마다 하나씩 정의된다.
		
	.rt file rule :
		◦ Each element first’s information is the type identifier 
		(composed by one or two character(s)), followed by all specific information
		 for each object in a strict order such as:
		--- obtion ---
		1. Resolution (해상도)
		2. Ambient lightning (주변광, 간접광)
		3. camera
		4. Light
		5. Sphere
		--- object ---
		6. Plane
		7. Square
		8. Cylinder
		9. Triangle

arg2 : save or no arg2
	"--save" : save rendered image in bmp
	no arg2  : 
		◦ Pressing ESC must close the window and quit the program cleanly.
		1. ESC 키 누를 경우

		◦ Clicking on the red cross on the window’s frame must close the window and
		quit the program cleanly.
		2. 창 닫기 누를 경우

		◦ If the declared size of the scene is greater than the display resolution, the
		window size will be set depending to the current display resolution.
		3. scene 의 정의된 크기가 the display resolution 보다 클 경우
			현재 display resolution 맞춰서 창이 생성된다.

		◦ If there is more than one camera you must be able to switch between them by
		pressing the keyboard keys of your choice.
		4. 1 개보다 많은 camera 가 있을 경우 keyboard 로 바꾸어가며 시점을 변경해야 한다.

		◦ The use of images of the minilibX is strongly recommended.
		5. minilibx 의 이미지 사용을 추천함

< 순서 > 
1. 에러 확인
	argument 개수 확인
	arg2 의 모양 확인 "--save"
2. 정보 담기
	rt file 값 확인
	구조체 이용
3. 계산
4. 표현
5. 출력 또는 저장
**/

#include "mini_rt.h"

int	main(int argc, char **argv)
{

	if (argc < 2)
	{
		// no arg1 and arg2
		// error
		print_error(1);
	}
	else if (argc >= 4)
	{
		// arg number must be 2 or 3
		// error
		print_error(2);
	}
	else
	{
		// arg2 check
		if (argc == 3)
		{
			if(ft_strncmp(argv[2], "--save", ft_strlen("--save")))
				print_error(3);
		}
		// .rt file check
	}
	return (0);
}