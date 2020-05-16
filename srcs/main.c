xzzz/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 11:44:13 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/15 22:48:24 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
	Program name 
		miniRT
	Turn in files 
		All your files
	Makefile 
		all, clean, fclean, re, bonus
	Arguments                       
		a scene in format *.rt
	External functs.
		• open, close, read, write,
		malloc, free, perror,
		strerror, exit
		• All functions of the math
		library (-lm man man 3 math)
		• All functions of the MinilibX
	Libft authorized
		Yes
	Description 
		The goal of your program is to generate images
		using the Raytracing protocol. Those computer
		generated images will each represent a scene, as
		seen from a specific angle and position, defined
		by simple geometric objects, and each with its own
	lighting system.

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
		< element >
			1~2 : only one
			3~9 : 1 <=
			--- option ---
			1. Resolution (해상도) - only one
				argument : x, y
			2. Ambient lightning (주변광, 간접광) - only one
			3. camera
			4. Light
			--- object ---
			5. Sphere
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
2. rt file 정보 담기(parsing)
	rt file 값 확인
	구조체 이용
3. 계산
	object sapce -> world space
	 : 이미 rt file 에서 모든 obeject 들이 동일한 좌표계에 위치
	world space -> view space(camera space)
	 : 카메라의 시점으로 만들어야한다. camera 시점에 따라 여러 개를 만든다.
	 : 월드공간에서 카메라 공간으로 바꾸기 위한 변환 행렬을 구해야한다.
	view space -> clip space
	 : 카메라의 시점으로 바라본 이미지를 2d 에 투영시커야한다.
	 : 원근 투시법 사용.
4. 표현
	어떤 이미지를 표현할지 선택한다.
5. 출력 또는 저장
	해당 이미지를 선택하여 window 에 띄운다.
**/

#include "mlx.h"
#include "mini_rt.h"

int	main(int argc, char **argv)
{
	t_rt *rt_info;

	if (argc < 2)
	{
		// no arg1 and arg2
		// error
		return(print_error("No argument!\n"));
	}
	else if (argc >= 4)
	{
		// arg number must be 2 or 3
		// error
		return(print_error("Argument number must be 2 or 3!\n"));
	}
	else
	{
		// arg2 check
		if (argc == 3)
		{
			if(ft_strncmp(argv[2], "--save", ft_strlen("--save")))
				return(print_error("Second argument is wrong format!\n"));
		}
		if(!(rt_info = malloc(sizeof(t_rt))))
			return (0);
		ft_bzero(rt_info, sizeof(t_rt));
		// .rt file check
		parsing_rt_file(argv[1], rt_info);
		// printf("t_r - size_x : %d\n", rt_info->t_r_->size_x_);
		// printf("t_r - size_y : %d\n", rt_info->t_r_->size_y_);
		// printf("t_a - light  : %f\n", rt_info->t_a_->light_);
		// printf("t_a - rgb  r : %d\n", rt_info->t_a_->rgb_.r_);
		// printf("t_a - rgb  g : %d\n", rt_info->t_a_->rgb_.g_);
		// printf("t_a - rgb  b : %d\n", rt_info->t_a_->rgb_.b_);
		// printf("t_a - cam  x : %f\n", rt_info->t_c_->vec_.x_);
		// printf("t_a - cam  y : %f\n", rt_info->t_c_->vec_.y_);
		// printf("t_a - cam  z : %f\n", rt_info->t_c_->vec_.z_);
	}
	// (void)argc;
	// if (check_str_isdouble(argv[1]))
	// 	printf("%f", ft_atof(argv[1]));
	// printf("%f", ft_atof("0"));
	return (0);
}


// #include <unistd.h>


// int	main()
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "hello mlx!");
// 	int i = 200;
// 	int j;
// 	while (i <= 250)
// 	{
// 		j = 200;
// 		while (j <= 300)
// 		{
// 			mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0xFFFFFF);
// 			j++;
// 		}	
// 		i++;
// 	}
// 	// mlx_key_hook(win_ptr, deal_key, (void*)0);
// 	mlx_loop(mlx_ptr);
// 	return (0);
// }
