/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:19:07 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/14 16:14:02 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
#define ELEMENT_H

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
	int		size_x;
	int		size_y;
}				t_r;

typedef struct s_ambient
{
	double 	light_;
	t_rgb	rgb_;
}				t_a;

typedef struct s_camera
{
	t_vec vec_;
	t_vec normal_vec_;
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
	double diameter;
}				t_sp;

typedef struct s_plane
{
	t_vec vec_;
	t_vec normal_vec_;
	double diameter;
	t_rgb rgb_;
}				t_pl;

typedef struct s_square
{
	t_vec vec_;
	t_vec normal_vec_;
	double side_size;
	t_rgb rgb_;
}				t_sq;

typedef struct s_cylinder
{
	t_vec vec_;
	t_vec normal_vec_;
	double diameter;
	double height;
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
	int		sy_;
	int		tr_;
	int		r_;
	int		a_;
	int		c_;
	int		l_;
}				t_count;

typedef struct s_rt_file_info
{
	t_count *count_;
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