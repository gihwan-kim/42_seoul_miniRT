/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:29:30 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/25 10:16:11 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

t_list		*get_object(t_list *cur_obj_pos)
{
	t_list *tmp;
	
	tmp = cur_obj_pos;
	if (cur_obj_pos == NULL)
		return (NULL);
	cur_obj_pos = cur_obj_pos->next;
	return (tmp);
}

// t_sp		*get_sphere(t_rt *rt_info)
// {
// 	t_sp *sphere;

// 	sphere = NULL;
// 	if (rt_info->count_->sp_)
// 		sphere = rt_info->lst_pos.cur_sp->content;
// 	return (sphere);
// }

