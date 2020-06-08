/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing_result.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 21:00:43 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/08 21:18:06 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// void	print_vec(const t_vec *vec)
// {
// 	printf("x : %f\t", vec->x_);
// 	printf("y : %f\t", vec->y_);
// 	printf("z : %f\n", vec->z_);
// }

// void	print_double(double d)
// {
// 	printf("%f\t", d);
// }

// void	print_matrix(t_matrix *m)
// {
// 	for (int i=0; i < 4; i++)
// 	{
// 		printf("matrix %d : ", i);
// 		for (int j=0; j < 4; j++)
// 		{
// 			print_double(m->matrix[i][j]);
// 		}
// 		printf("\n");
// 	}
// }

// void	print_rgb_f(const t_rgb_f *rgb)
// {
// 	printf("r : %f\t", rgb->r_);
// 	printf("g : %f\t", rgb->g_);
// 	printf("b : %f\n", rgb->b_);
// }

// void	print_light(t_l *light)
// {
// 	printf("[위치] \t");
// 	print_vec(&(light->vec_));
// 	printf("[rgb] \t");
// 	print_rgb_f(&(light->rgb_));
// 	printf("[ratio] \t%f\n", light->light_);
// }



//  void	check_light(t_rt *rt_info)
// {
// 	t_list	*cur_light_node;
// 	t_l		*light;

// 	cur_light_node = get_node(&(rt_info->lst_pos.cur_l));
// 	while (cur_light_node)
// 	{
// 		light = (t_l*)(cur_light_node->content);
// 		print_light(light);
// 		cur_light_node = get_node(&(rt_info->lst_pos.cur_l));
// 	}
// 	if (rt_info->count_->l_)
// 		rt_info->lst_pos.cur_l = rt_info->lst_pos.fst_l;
// }

// void	check_ambient(t_rt *rt_info)
// {
// 	printf("[rgb] \t");
// 	print_rgb_f(&(rt_info->t_a_->rgb_));
// 	printf("[ratio] \t%f\n", rt_info->t_a_->light_);
// }

// void	check_camera(t_rt *rt_info)
// {
// 	t_list	*cur_light_node;
// 	t_c		*light;

// 	cur_light_node = get_node(&(rt_info->lst_pos.cur_c));
// 	while (cur_light_node)
// 	{
// 		light = (t_c*)(cur_light_node->content);
// 		printf("[위치] \t");
// 		print_vec(&(light->vec_));
// 		printf("[방향] \t");
// 		print_vec(&(light->orient_vec_));
// 		printf("[ up ] \t");
// 		print_vec(&(light->up_));
// 		printf("[fov ] \t%f\n", light->fov_);
// 		cur_light_node = get_node(&(rt_info->lst_pos.cur_c));
// 	}
// }

// void	check_sphere(t_rt *rt_info)
// {
// 	t_list	*cur_light_node;
// 	t_sp		*light;

// 	cur_light_node = get_node(&(rt_info->lst_pos.cur_sp));
// 	while (cur_light_node)
// 	{
// 		light = (t_sp*)(cur_light_node->content);
// 		printf("[위치] \t");
// 		print_vec(&(light->vec_));
// 		printf("[rgb] \t");
// 		print_rgb_f(&(light->rgb_));
// 		printf("[지름] \t%f\n", light->diameter_);
// 		cur_light_node = get_node(&(rt_info->lst_pos.cur_sp));
// 	}	
// }

// void	check_plane(t_rt *rt_info)
// {
// 	t_list	*cur_light_node;
// 	t_pl	*light;

// 	cur_light_node = get_node(&(rt_info->lst_pos.cur_pl));
// 	while (cur_light_node)
// 	{
// 		light = (t_pl*)(cur_light_node->content);
// 		printf("[위치] \t");
// 		print_vec(&(light->vec_));
// 		printf("[방향] \t");
// 		print_vec(&(light->orient_vec_));
// 		printf("[rgb] \t");
// 		print_rgb_f(&(light->rgb_));
// 		printf("[지름] \t%f\n", light->diameter_);
// 		cur_light_node = get_node(&(rt_info->lst_pos.cur_pl));
// 	}	
// }

// void	check_square(t_rt *rt_info)
// {
// 	t_list	*cur_light_node;
// 	t_sq	*light;

// 	cur_light_node = get_node(&(rt_info->lst_pos.cur_sq));
// 	while (cur_light_node)
// 	{
// 		light = (t_sq*)(cur_light_node->content);
// 		printf("[위치] \t");
// 		print_vec(&(light->vec_));
// 		printf("[방향] \t");
// 		print_vec(&(light->orient_vec_));
// 		printf("[rgb] \t");
// 		print_rgb_f(&(light->rgb_));
// 		printf("[크기] \t%f\n", light->side_size);
// 		cur_light_node = get_node(&(rt_info->lst_pos.cur_sq));
// 	}	
// }

// void	check_cylinder(t_rt *rt_info)
// {
// 	t_list	*cur_light_node;
// 	t_cy	*light;

// 	cur_light_node = get_node(&(rt_info->lst_pos.cur_cy));
// 	while (cur_light_node)
// 	{
// 		light = (t_cy*)(cur_light_node->content);
// 		printf("[위치] \t");
// 		print_vec(&(light->vec_));
// 		printf("[방향] \t");
// 		print_vec(&(light->orient_vec_));
// 		printf("[rgb] \t");
// 		print_rgb_f(&(light->rgb_));
// 		printf("[크기] \t%f\n", light->diameter_);
// 		printf("[높이] \t%f\n", light->height_);
// 		cur_light_node = get_node(&(rt_info->lst_pos.cur_cy));
// 	}	
// }

// void	check_triangle(t_rt *rt_info)
// {
// 	t_list	*cur_light_node;
// 	t_tr	*light;

// 	cur_light_node = get_node(&(rt_info->lst_pos.cur_tr));
// 	while (cur_light_node)
// 	{
// 		light = (t_tr*)(cur_light_node->content);
// 		printf("[위치] \t");
// 		print_vec(&(light->vec_1_));
// 		printf("[위치] \t");
// 		print_vec(&(light->vec_2_));
// 		printf("[위치] \t");
// 		print_vec(&(light->vec_3_));
// 		printf("[방향] \t");
// 		print_vec(&(light->normal));
// 		printf("[rgb] \n");
// 		print_rgb_f(&(light->rgb_));
// 		cur_light_node = get_node(&(rt_info->lst_pos.cur_tr));
// 	}	
// }

