/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:19:07 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/19 16:56:18 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
#define ELEMENT_H
/*
** t_rgb
** 		: R,G,B colors in range [0-255]
** float light
** 		: ambient lighting ratio in range [0.0,1.0]:
** float fov
** 		: Horizontal field of view in degrees in range [0,180]
** t_vec orient_vec_
**		: · 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
*/
typedef struct s_vector
{
	double x_;
	double y_;
	double z_;
}				t_vec;

typedef struct s_rgb
{
	int		r_;
	int 	g_;
	int		b_;
}				t_rgb;

typedef struct s_resolution
{
	int		size_x_;
	int		size_y_;
}				t_r;

typedef struct s_ambient
{
	double 	light_;
	t_rgb	rgb_;
}				t_a;

typedef struct s_camera
{
	t_vec vec_;
	t_vec orient_vec;
	t_vec up_;
	t_vec n_; // z
	t_vec v_; // y
	t_vec u_; // x

	
	double fov_;
}				t_c;

typedef struct s_light
{
	t_vec vec_;
	t_rgb rgb_;
	double light_;
}				t_l;

typedef struct s_sphere
{
	t_vec vec_;
	t_rgb rgb_;
	double diameter_;
}				t_sp;

typedef struct s_plane
{
	t_vec vec_;
	t_vec orient_vec;
	double diameter_;
	t_rgb rgb_;
}				t_pl;

typedef struct s_square
{
	t_vec vec_;
	t_vec orient_vec;
	double side_size;
	t_rgb rgb_;
}				t_sq;

typedef struct s_cylinder
{
	t_vec vec_;
	t_vec orient_vec;
	double diameter_;
	double height_;
	t_rgb rgb_;
}				t_cy;

typedef struct s_triangle
{
	t_vec vec_1st_;
	t_vec vec_2nd_;
	t_vec vec_3rd_;
	t_rgb rgb_;
}				t_tr;

typedef struct s_count
{
	int		sp_;
	int		pl_;
	int		sq_;
	int		cy_;
	int		tr_;
	int		r_;
	int		a_;
	int		c_;
	int		l_;
}				t_count;

typedef struct	s_image
{
	void		*img_ptr;
	int			*data;
	// 실제 color 값이 담길 배열
	//Here you got an int * even though mlx_get_data_addr returns
	//a char *, i'll talk more about this in the .c file.
	//Here are the 3 "useless" variables. You can find more informations about these in the man page.
	int			size_l;
	int			bpp;
	int			endian;
	t_c			*camera;
	
}				t_img;

typedef struct s_rt_file_info
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img_;
	t_count *count_;
	t_r		*t_r_;
	t_a		*t_a_;

	t_list	*lst_sp_;
	t_list	*lst_pl_;
	t_list	*lst_sq_;
	t_list	*lst_cy_;
	t_list	*lst_tr_;
	t_list	*lst_c_;
	t_list	*lst_l_;
}				t_rt;

#endif