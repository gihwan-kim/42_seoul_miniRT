/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 11:08:04 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/14 00:09:08 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define ERROR 0
# define SUCCESS 1
#include <stdio.h>
#include "error.h"
#include "parsing.h"
#include "../lib/libft/include/get_next_line.h"
#include "../lib/libft/include/libft.h"


/*
** t_vec normal_vec_;
** 		: 3d normalized orientation vector. In range [-1,1]
** t_rgb
** 		: R,G,B colors in range [0-255]
** float light
** 		: ambient lighting ratio in range [0.0,1.0]:
** float fov
** 		: Horizontal field of view in degrees in range [0,180]
*/

typedef struct s_vector
{
	float x;
	float y;
	float z;
}				t_vec;

typedef struct s_rgb
{
	int		r;
	int 	g;
	int		b;
}				t_rgb;

typedef struct s_resolution
{
	t_vec vec_;
}				t_r;

typedef struct s_ambient
{
	float 	light_;
	t_rgb	rgb_

}				t_a;

typedef struct s_camera
{
	t_vec vec_;
	t_vec normal_vec_;
	float fov_;
}				t_c;

typedef struct s_light
{
	t_vec vec_;
	float light_;
	t_rgb rgb_;
}				t_l;


typedef struct s_sphere
{
	t_vec vec_;
	float diameter;
	t_rgb rgb_;
}				t_sp;

typedef struct s_plane
{
	t_vec vec_;
	t_vec normal_vec_;
	float diameter;
	t_rgb rgb_;
}				t_pl;

typedef struct s_square
{
	t_vec vec_;
	t_vec normal_vec_;
	float side_size;
	t_rgb rgb_;
}				t_sq;

typedef struct s_cylinder
{
	t_vec vec_;
	t_vec normal_vec_;
	float diameter;
	float height;
	t_rgb rgb_;
}				t_cy;

typedef struct s_triangle
{
	t_vec vec_1st_;
	t_vec vec_2nd_;
	t_vec vec_3rd_;
	t_rgb rgb_;
}				t_tr;

typedef struct s_rt_file_info
{

	t_sp	*t_sp_;
	t_pl	*t_pl_;
	t_sq	*t_sq_;
	t_cy	*t_sy_;
	t_tr	*t_tr_;
	t_r		*t_r_;
	t_a		*t_a_;
	t_c		*t_c_;
	t_l		*t_l_;
}				t_rt;
#endif