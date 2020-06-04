/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_controller.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:54:53 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/04 21:55:10 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

static void	reset_obejct_pos(t_lst_position *lst_pos, t_count* count)
{
	if (count->sp_)
		lst_pos->cur_sp = lst_pos->fst_sp;
	if (count->cy_)
		lst_pos->cur_cy = lst_pos->fst_cy;
	if (count->pl_)
		lst_pos->cur_pl = lst_pos->fst_pl;
	if (count->tr_)
		lst_pos->cur_tr = lst_pos->fst_tr;
	if (count->sq_)
		lst_pos->cur_sq = lst_pos->fst_sq;
}

int		intersection_controller(t_rt *rt_info, t_ray *ray, t_phit *h_obj_info, double *tnear, t_obj_count *c)
{
	double	cur_t;	
	int		i;
	void	*ret;
	t_e_obj	type;

	i = -1;
	if (!(rt_info->count_->all_obj))
		return (print_error_comment("There are 0 object!", rt_info));
	while (++i < rt_info->count_->all_obj)
	{
		ret = check_intersection(rt_info, ray, &type, &cur_t, c);
		if (ret)
		{
			// write(1, "near check\n", 12);
			// printf("cur_t : %f\ttnear : %f\n", cur_t, *tnear);
			if (cur_t < *tnear)
			{
				// write(1, "checked\n", 9);
				*tnear = cur_t;
				h_obj_info->obj = ret;
				h_obj_info->type = type;
				type = 0;
			}
		}
	}
	// write(1, "pos check\n", 11);
	reset_obejct_pos(&(rt_info->lst_pos), rt_info->count_);
	// write(1, "obj check\n", 11);
	if (h_obj_info->obj)
	{
		// write(1, "checked\n", 11);
		return (TRUE);
	}
	return (FALSE);
}

void	*check_intersection(t_rt *rt_info, t_ray *ray, t_e_obj *type,
							double *t, t_obj_count *c)
{
	void	*ret;

	ret = NULL;
	if ((ret = intersection_sphere(rt_info, ray, t)))
	{
		*type = sphere;
		c->sp += 1;
		return (ret);
	}
	else if ((ret = intersection_plane(rt_info, ray, t)))
	{
		*type = plane;
		c->pl += 1;
		// printf("plane!\n");
		return (ret);
	}
	else if ((ret = intersection_square(rt_info, ray, t)))
	{
		*type = square;
		c->sq += 1;
		// printf("square!\n");
		return (ret);
	}
	else if ((ret = intersection_cylinder(rt_info, ray, t)))
	{
		*type = cylinder;
		c->cy += 1;
		// printf("cylinder!\n");
		return (ret);
	}
	else if ((ret = intersection_triangle(rt_info, ray, t)))
	{
		*type = triangle;
		c->tr += 1;

		// printf("triangle!\n");
		return (ret);
	}
	return (ret);
}