/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 11:44:13 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/08 21:03:46 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	make_window(t_rt *rt_info)
{
	int		width;
	int		height;

	width = rt_info->t_r_->size_x_;
	height = rt_info->t_r_->size_y_;
	rt_info->mlx_ptr = mlx_init();
	rt_info->win_ptr = mlx_new_window(rt_info->mlx_ptr, width, height, "mini ray-tracing");
	rt_info->img_.img_ptr = mlx_new_image(rt_info->mlx_ptr, width, height);
	rt_info->img_.data = (int *)mlx_get_data_addr(rt_info->img_.img_ptr,
		&rt_info->img_.bpp, &rt_info->img_.size_l, &rt_info->img_.endian);
}

static void	render(t_rt *rt_info)
{
	t_c	*camera;
	int	width;
	int height;

	if (isempty_node(rt_info->lst_pos.cur_c))
		camera = get_node(&(rt_info->lst_pos.cur_c))->content;
	else
	{
		camera = rt_info->lst_pos.fst_c->content;
		rt_info->lst_pos.cur_c = rt_info->lst_pos.fst_c;
		ft_putendl_fd("No next camera!\nSet camera to first camera node!", 1);
	}
	width = rt_info->t_r_->size_x_;
	height = rt_info->t_r_->size_y_;
	if (make_img(rt_info, camera, width, height) == ERROR)
	{
		print_error_comment("image make fail!", rt_info);
		exit(EXIT_FAILURE);
	}
	mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr, 
			rt_info->img_.img_ptr, 0, 0);
}

static int	ft_key_press(int keycode, t_rt *rt_info)
{
	if (keycode == 123)
	{
		ft_putendl_fd("Change camera", 1);
		render(rt_info);
	}
	return (0);
}

static int	ft_close(t_rt *rt_info)
{
	(void)rt_info;
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_rt *rt_info;

	if (argc < 2)
		return(print_error_nofree(22, "No argument!"));
	else if (argc >= 4)
		return(print_error_nofree(23, "Argument number must be 2 or 3!"));
	else
	{
		if (argc == 3)
		{
			if(ft_strncmp(argv[2], "--save", ft_strlen("--save")))
				return(print_error_nofree(22, "wrong format!"));
		}
		if(!(rt_info = malloc(sizeof(t_rt))))
			return (0);
		ft_bzero(rt_info, sizeof(t_rt));
		parsing_rt_file(argv[1], rt_info);
		make_window(rt_info);
		// if(!make_img(rt_info, rt_info->t_r_->size_x_, rt_info->t_r_->size_y_))
		// 	return print_error_comment("image make fail!", rt_info);
		render(rt_info);
		mlx_hook(rt_info->win_ptr, 2, 0, ft_key_press, rt_info);
		mlx_hook(rt_info->win_ptr, 17, 0, ft_close, rt_info);
		mlx_loop(rt_info->mlx_ptr);
	}
	return (0);
}
