/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_controller.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:54:53 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/01 18:41:16 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

static void	reset_obejct_pos(t_lst_position *lst_pos)
{
	lst_pos->cur_cy = lst_pos->fst_cy;
	lst_pos->cur_pl = lst_pos->cur_pl;
	lst_pos->cur_sp = lst_pos->fst_sp;
	lst_pos->cur_sq = lst_pos->fst_tr;
	lst_pos->cur_sq = lst_pos->fst_sq;
}

int		intersection_controller(t_rt *rt_info, t_ray *ray, t_phit *h_obj_info, double *tnear)
{
	double	cur_t;	
	int		i;
	void	*ret;
	t_e_obj	type;
	// t_phit	*hit_obj;
	
	// hit_obj = &(rt_info->img_.hit_obj);
	// hit_obj->obj = NULL;
	i = -1;
	if (!(rt_info->count_->all_obj))
		return (print_error_comment("There are 0 object!", rt_info));
	while (++i < rt_info->count_->all_obj)
	{
		ret = check_intersection(rt_info, ray, &type, &cur_t);
		if (ret)
		{
			if (cur_t < *tnear)
			{
				*tnear = cur_t;
				h_obj_info->obj = ret;
				h_obj_info->type = type;
				// hit_obj->obj = ret;
				// hit_obj->type = type;
				type = 0;
			}
		}
	}
	reset_obejct_pos(&(rt_info->lst_pos));
	// if (hit_obj->obj)
	// 	return (TRUE);
	if (h_obj_info->obj)
		return (TRUE);
	return (FALSE);
}

void	*check_intersection(t_rt *rt_info, t_ray *ray, t_e_obj *type,
							double *t)
{
	void	*ret;

	ret = NULL;
	if ((ret = intersection_sphere(rt_info, ray, t)))
	{
		*type = sphere;
		return (ret);
	}
	else if ((ret = intersection_plane(rt_info, ray, t)))
	{
		*type = plane;
		printf("plane!\n");
		return (ret);
	}
	else if ((ret = intersection_square(rt_info, ray, t)))
	{
		*type = square;
		printf("square!\n");
		return (ret);
	}
	else if ((ret = intersection_cylinder(rt_info, ray, t)))
	{
		*type = cylinder;
		printf("cylinder!\n");
		return (ret);
	}
	else if ((ret = intersection_triangle(rt_info, ray, t)))
	{
		*type = triangle;
		printf("triangle!\n");
		return (ret);
	}
	return (ret);
}