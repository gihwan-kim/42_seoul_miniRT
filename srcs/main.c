/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 11:44:13 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/28 09:19:26 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	make_window(t_rt *rt_info)
{
	int		width;
	int		height;

	width = rt_info->t_r_->size_x_;
	height = rt_info->t_r_->size_y_;
	rt_info->mlx_ptr = mlx_init();
	rt_info->win_ptr = mlx_new_window(rt_info->mlx_ptr, width, height, "RT");
	rt_info->img_.img_ptr = mlx_new_image(rt_info->mlx_ptr, width, height);
	rt_info->img_.data = (int *)mlx_get_data_addr(rt_info->img_.img_ptr,
		&rt_info->img_.bpp, &rt_info->img_.size_l, &rt_info->img_.endian);
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
		if(!make_img(rt_info, rt_info->t_r_->size_x_, rt_info->t_r_->size_y_))
			return print_error_comment("image make fail!", rt_info);
		mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr, 
			rt_info->img_.img_ptr, 0, 0);
		mlx_loop(rt_info->mlx_ptr);
	}
	return (0);
}

	// (void)argc;
	// if (check_str_isdouble(argv[1]))
	// 	printf("%f", ft_atof(argv[1]));
	// printf("%f", ft_atof("0"));
		// printf("t_r - size_x : %d\n", rt_info->t_r_->size_x_);
		// printf("t_r - size_y : %d\n", rt_info->t_r_->size_y_);
		// printf("t_a - light  : %f\n", rt_info->t_a_->light_);
		// printf("t_a - rgb  r : %d\n", rt_info->t_a_->rgb_.r_);
		// printf("t_a - rgb  g : %d\n", rt_info->t_a_->rgb_.g_);
		// printf("t_a - rgb  b : %d\n", rt_info->t_a_->rgb_.b_);
		// printf("t_a - cam  x : %f\n", rt_info->t_c_->vec_.x_);
		// printf("t_a - cam  y : %f\n", rt_info->t_c_->vec_.y_);
		// printf("t_a - cam  z : %f\n", rt_info->t_c_->vec_.z_);

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
