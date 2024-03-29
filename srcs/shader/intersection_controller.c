/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_controller.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:54:53 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 22:25:14 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

static void	reset_obejct_pos(t_lst_position *lst_pos, t_count *count)
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

int			intersection_controller(t_rt *rt_info,
									t_ray *ray,
									t_phit *h_obj_info,
									double *tnear)
{
	double	cur_t;
	int		i;
	void	*ret;
	t_e_obj	type;

	i = -1;
	*tnear = T_INFINITY;
	if (!(rt_info->count_->all_obj))
		return (print_error_comment("There are 0 object!", rt_info));
	while (++i < rt_info->count_->all_obj)
	{
		ret = check_intersection(rt_info, ray, &type, &cur_t);
		if (ret && cur_t < *tnear)
		{
			*tnear = cur_t;
			h_obj_info->obj = ret;
			h_obj_info->type = type;
			type = 0;
		}
	}
	reset_obejct_pos(&(rt_info->lst_pos), rt_info->count_);
	if (h_obj_info->obj)
		return (TRUE);
	return (FALSE);
}

void		*check_intersection(t_rt *rt_info, t_ray *ray, t_e_obj *type,
							double *t)
{
	void	*ret;

	ret = NULL;
	if ((ret = intersection_sphere(rt_info, ray, t)))
		*type = sphere;
	else if ((ret = intersection_plane(rt_info, ray, t)))
		*type = plane;
	else if ((ret = intersection_square(rt_info, ray, t)))
		*type = square;
	else if ((ret = intersection_cylinder(rt_info, ray, t)))
		*type = cylinder;
	else if ((ret = intersection_triangle(rt_info, ray, t)))
		*type = triangle;
	return (ret);
}
