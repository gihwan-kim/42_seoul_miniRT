/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:09:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 17:58:29 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** hit_n is orthogonal to hit point
** normal 은 물체 반대방향을 가리키면안됨
** camera 쪽을 바라봐야함
** camera_ray direction 과 normal 의 각은 둔각이 되어야한다.
*/
static	void 	calc_normal(t_phit *obj_info, t_ray *ray)
{
	t_e_obj hit_obj_type;
	void	*obj;

	hit_obj_type = obj_info->type;
	obj = obj_info->obj;
	if (hit_obj_type == plane)
		obj_info->hit_normal = make_plane_normal((t_pl*)obj);
	else if (hit_obj_type == sphere)
		obj_info->hit_normal = make_sphere_normal((t_sp*)obj, &(obj_info->hit_point));
	else if (hit_obj_type == cylinder)
		obj_info->hit_normal = make_cylinder_normal((t_cy*)obj, &(obj_info->hit_point));
	else if (hit_obj_type == square)
		obj_info->hit_normal = make_square_normal((t_sq*)obj);
	else if (hit_obj_type == triangle)
		obj_info->hit_normal = make_triangle_normal((t_tr*)obj);
	if (dot_product(&(obj_info->hit_normal), &(ray->direction_)) > 0)
		vec_inverse(&(obj_info->hit_normal));
}

static t_rgb_f	calc_specular(t_ray *shadow_ray, t_phit *obj_info,
												t_rgb_f *light_color)
{
	t_rgb_f	specular_color;
	t_vec	inverse_cam_ray_direction;
	t_vec	reflection_ray_direction;
	double	n_dot_s;
	double	r_dot_c;

	inverse_cam_ray_direction = obj_info->cam_ray->direction_;
	vec_inverse(&inverse_cam_ray_direction);
	n_dot_s = fmax(dot_product(&(obj_info->hit_normal),
									&(shadow_ray->direction_)), 0.0);
	reflection_ray_direction = multiply(&(obj_info->hit_normal), n_dot_s);
	reflection_ray_direction = multiply(&reflection_ray_direction, 2.0);
	reflection_ray_direction = subtract(&reflection_ray_direction,
										&(shadow_ray->direction_));
	r_dot_c = fmax(dot_product(&reflection_ray_direction,
						&inverse_cam_ray_direction), 0.0);
	r_dot_c = pow(r_dot_c, 10);
	specular_color = init_color(0.9); //high light
	specular_color = colorf_multi_colorf(light_color, &(specular_color));
	specular_color = multi_colorf(&specular_color, r_dot_c);
	return (specular_color);
}

static void		reset_light_pos(t_lst_position *lst_pos, t_count* count)
{
	if (count->l_)
		lst_pos->cur_l = lst_pos->fst_l;
}

/*
** light_dir  : camera ray 와 물체가 충돌한 지점 -> 광원까지 방향벡터
** shadow_ray(Incidence ray 의 반대방향)
**	 : 충돌지점->광원 벡터
**	 : shadow 를 만드는데 사용 -> intersection_controller 함수 사용하여 확인
** facing Ratio : 
**	 : n ● v
**	 : n - hit_point 를 지나는 접선의 수직인 벡터
**	 : v - hit_point -> 광원 방향인 normal 벡터
**	 : n ● v 의 값에 따라 그 점의 밝기가 달라진다.
**	 : famx(a, b) a 와 b 중 큰 값을 리턴한다
** vis
**	 : shadow 유뮤, intersection_controller 가 ture 이면 shadow 가 있다고 판단한다.
**	 : vis 가 true 일 경우 color 에 곱할때 값은 변하지 않을 것이다.
** bias
**	 : Shadow-Acne: Avoiding Self-Intersection
*/

static	t_rgb_f calc_color(t_rt *rt_info, t_l *light_source, t_phit *obj_info)
{
	t_phit	nothing;
	t_color color;
	t_ray	shadow_ray;
	double	t;
	double	facing_ratio;

	shadow_ray.direction_ = subtract(&(light_source->vec_), &(obj_info->hit_point));
	shadow_ray.len = vector_len(&(shadow_ray.direction_));
	shadow_ray.direction_ = normalize(&(shadow_ray.direction_));
	shadow_ray.origin_ = multiply(&(obj_info->hit_normal), 0.1);
	shadow_ray.origin_ = add(&(obj_info->hit_point), &(shadow_ray.origin_));
	facing_ratio = 0;
	if (!intersection_controller(rt_info, &shadow_ray, &nothing, &t)
		|| t > shadow_ray.len)
		facing_ratio = fmax(0.0, dot_product(&(obj_info->hit_normal),
							&(shadow_ray.direction_)));
	color.light = multi_colorf(&(light_source->rgb_), light_source->light_);
	color.final = colorf_multi_colorf(&(color.light), &(obj_info->colorf));
	color.final = multi_colorf(&(color.final), facing_ratio);
	if (facing_ratio)
	{
		color.specular = calc_specular(&shadow_ray, obj_info, &(color.light));
		// color.specular = colorf_multi_colorf(&(color.specular), &(obj_info->colorf));
		color.final = add_color(&(color.final), &(color.specular));
	}
	// if (!facing_ratio)
	// 	printf("%d", nothing.type);
	return (color.final);
}

/*
** while loop : combination lights result(specular, diffuse) to color
** after while loop add ambient to color
*/

int			pixel_shader(t_rt *rt_info, t_ray *camera_ray, double *t, t_phit *obj_info)
{
	t_list	*cur_light_node;
	t_rgb_f	calc_result;
	t_rgb_f ambient_color;
	t_rgb_f	color;
	t_rgb	value;

	obj_info->hit_point = calc_hit_point(camera_ray, t);
	calc_normal(obj_info, camera_ray);
	obj_info->cam_ray = camera_ray;
	color = init_color(0.0);
	while (isempty_node(rt_info->lst_pos.cur_l, rt_info->count_->l_))
	{
		cur_light_node = get_node(&(rt_info->lst_pos.cur_l));
		calc_result = calc_color(rt_info, (t_l*)(cur_light_node->content), obj_info);
		color = add_color(&color, &calc_result);
	}
	reset_light_pos(&(rt_info->lst_pos), rt_info->count_);
	ambient_color =	multi_colorf(&(rt_info->t_a_->rgb_), rt_info->t_a_->light_);
	ambient_color = colorf_multi_colorf(&(ambient_color), &(obj_info->colorf));
	color = add_color(&color, &ambient_color);
	value.r_ = color.r_ * 256;
	value.g_ = color.g_ * 256;
	value.b_ = color.b_ * 256;
	return (65536 * value.r_ + 256 * value.g_ + value.b_);
}
