/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 21:27:23 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/07 13:04:16 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** hit point must be between top cap and bottom cap
** q = p + v t (p-rayorigin, v-raydirection) 
*/

static int	check_cur_t(double *t, t_ray *ray, t_cy *cy)
{
	t_vec	hit_point;
	t_vec	multi_result;
	t_vec	bottom_cap_center;
	t_vec	up_cap_center;
	t_vec	q_to_center;
	
	if (t < 0)
		return (FALSE);
	bottom_cap_center = cy->vec_;
	multi_result = multiply(&(cy->orient_vec_), cy->height_);
	up_cap_center = add(&(cy->vec_), &multi_result);
	hit_point = calc_hit_point(ray, t);
	q_to_center = subtract(&hit_point, &bottom_cap_center);
	if (dot_product(&(cy->orient_vec_), &q_to_center) <= 0)
		return (FALSE);
	q_to_center = subtract(&hit_point, &up_cap_center);
	if (dot_product(&(cy->orient_vec_), &q_to_center) >= 0)
		return (FALSE);
	return (TRUE);
}

/*
** t_0, t_1 not negative
** hit point must be between bottom cap and top cap
*/

static int	check_t_and_set_t(t_vec *quad_info, double *t, t_ray *ray, t_cy *cy)
{
	double	t_0;
	double	t_1;
	double	ret0;
	double	ret1;

	if(!quadratic_formula(quad_info, &t_0, &t_1))
		return (FALSE);
	ret0 = check_cur_t(&t_0 ,ray, cy);
	ret1 = check_cur_t(&t_1 ,ray, cy);
	if (!ret0 && !ret1)
		return (FALSE);
	if (ret0 && !ret1)
		*t = t_0;
	if (!ret0 && ret1)
		*t = t_1;
	if (ret0 && ret1)
		*t = (t_0 < t_1) ? t_0 : t_1;
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

	if (isempty_node(rt_info->lst_pos.cur_cy))
		cylinder = get_node(&(rt_info->lst_pos.cur_cy))->content;
	else
		return (NULL);
	cylinder->orient_vec_ = normalize(&(cylinder->orient_vec_));
	quad_sqrt_1 = get_quadrtaic_sqrt(ray, cylinder, 1);
	quadratic_info.x_ = dot_product(&quad_sqrt_1, &quad_sqrt_1);
	quad_sqrt_2 = get_quadrtaic_sqrt(ray, cylinder, 0);
	quadratic_info.y_= 2 * dot_product(&quad_sqrt_1, &quad_sqrt_2);
	quadratic_info.z_ = dot_product(&quad_sqrt_2, &quad_sqrt_2)
						- (cylinder->diameter_ / 2.0) * (cylinder->diameter_ / 2.0);
	if (check_t_and_set_t(&quadratic_info, t, ray, cylinder))
		return (cylinder);
	else
		return (NULL);
}
