/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 21:27:23 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/03 13:54:48 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** check == 1 : check top cap
** check == 0 : check bottom cap
** check cur_t is inside between bottom and top of cylinder
** q = p + v t (p-rayorigin, v-raydirection)
*/

static int	check_cur_t(int	check, double cur_t, t_ray *ray, t_cy *cy)
{
	double	check_cap;
	t_vec	q;
	t_vec	q_to_cap_center;
	t_vec	cap_center;
	t_vec	multi_result;

	multi_result = multiply(&(cy->orient_vec_), cy->height_);
	if (check)
		cap_center = add(&(cy->vec_), &multi_result);
	else
		cap_center = cy->vec_;
	multi_result = multiply(&(ray->direction_), cur_t);
	q = add(&(ray->origin_), &multi_result);
	q_to_cap_center = subtract(&q, &cap_center);
	check_cap = dot_product(&(ray->direction_), &q_to_cap_center);
	if (check)
	{
		if (check_cap < 0)
			return (TRUE);
	}
	else
	{
		if (check_cap > 0)
			return (TRUE);
	}
	return (FALSE);
}

/*
** t_0, t_1 not negative
*/

int		check_t_and_set_t(t_vec *quad_info, double *t, t_ray *ray, t_cy *cy)
{
	double	t_0;
	double	t_1;

	if(!quadratic_formula(quad_info, &t_0, &t_1))
		return (ERROR);
	if (t_0 != t_1)
	{
		if (t_1 < 0)
			return (FALSE);
		if (!check_cur_t(0, t_1, ray, cy) || !check_cur_t(0, t_1, ray, cy))
			return (FALSE);
	}
	if (t_0 < 0)
		return (FALSE);
	if (!check_cur_t(0, t_0, ray, cy) || !check_cur_t(0, t_1, ray, cy))
		return (FALSE);
	*t = (t_0 <= t_1) ? t_0 : t_1;
	return (SUCCESS);
}

static	t_vec	get_quadrtaic_sqrt(t_ray *ray, t_cy	*cylinder, int check)
{
	t_vec	quadtratic_sqrt;
	t_vec	delta;
	t_vec	multi_result;
	double	dot_result;

	if (check)
	{
		dot_result = dot_product(&(ray->direction_), &(cylinder->orient_vec_));
		multi_result = multiply(&(cylinder->orient_vec_), dot_result);
		quadtratic_sqrt = subtract(&(ray->direction_), &multi_result);
	}
	else
	{
		delta = subtract(&(ray->origin_), &(cylinder->vec_));
		dot_result = dot_product(&(delta), &(cylinder->orient_vec_));
		multi_result = multiply(&(cylinder->orient_vec_), dot_result);
		quadtratic_sqrt = subtract(&(delta), &multi_result);
	}
	return (quadtratic_sqrt);
}

t_cy	*intersection_cylinder(t_rt *rt_info, t_ray *ray, double *t)
{
	t_vec	quadratic_info;
	t_vec	quad_sqrt_1;
	t_vec	quad_sqrt_2;
	t_cy	*cylinder;

	// if (!(cylinder = get_node(rt_info->lst_pos.cur_cy)->content))
	// 	return (SUCCESS);
	if (isempty_node(rt_info->lst_pos.cur_cy))
		// cylinder = get_node(rt_info->lst_pos.cur_cy)->content;
		cylinder = get_node(&(rt_info->lst_pos.cur_cy))->content;
	else
		return (NULL);
	quad_sqrt_1 = get_quadrtaic_sqrt(ray, cylinder, 1);
	quadratic_info.x_ = pow(vector_len(&quad_sqrt_1), 2.0);
	quad_sqrt_2 = get_quadrtaic_sqrt(ray, cylinder, 0);
	quadratic_info.y_= 2.0 * dot_product(& quad_sqrt_1, &quad_sqrt_2);
	quadratic_info.z_ = pow(vector_len(&quad_sqrt_2), 2.0)
						- pow(cylinder->diameter_, 2.0);
	if (check_t_and_set_t(&quadratic_info, t, ray, cylinder))
		return (cylinder);
	else
		return (NULL);
}
