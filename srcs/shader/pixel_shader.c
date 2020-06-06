/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:09:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/06 10:56:12 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** hit_n is orthogonal to hit point
** normal 은 물체 반대방향을 가리키면안됨
** camera 쪽을 바라봐야함
** camera_ray direction 과 normal 의 각은 둔각이 되어야한다.
*/
// static void	calc_normal(t_rt *rt_info,
// 						t_vec *hit_p,
// 						t_vec *hit_n,
// 						t_ray *ray)
static	void calc_normal(t_phit *obj_info, t_ray *ray)
{
	t_e_obj hit_obj_type;
	// t_vec	*hit_n_ptr;
	// t_vec	*hit_p_ptr;
	void	*obj;

	// hit_p_ptr = &(obj_info->hit_point);
	// hit_p_ptr = &(obj_info->hit_normal);
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

// static	t_rgb_f	calc_specular(t_ray *shadow_ray, t_phit *obj_info,
// 												t_l *light_source)
static t_rgb_f	calc_specular(t_ray *shadow_ray, t_phit *obj_info,
												t_rgb_f *light_color)
{
	t_vec	inverse_cam_ray_direction;
	t_vec	reflection_ray_direction;
	t_rgb_f	specular_color;
	double	n_dot_s;
	double	r_dot_c;

	// inverse_cam_ray_direction = shadow_ray->direction_;
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
	// specular = colorf_multi_colorf(&(light_source->rgb_), &(obj_info->colorf));
	specular_color.r_ = 0.9;
	specular_color.g_ = 0.9;
	specular_color.b_ = 0.9;
	
	// specular_color = colorf_multi_colorf(light_color, &(obj_info->colorf));
	specular_color = colorf_multi_colorf(light_color, &(specular_color));
	specular_color = multi_colorf(&specular_color, r_dot_c);
	return (specular_color);
}

static	void	reset_light_pos(t_lst_position *lst_pos, t_count* count)
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

	// vis true or len 보다 t 가 더 클 경우 -> 물체 빛 or 물체 빛 물체 순서
	//	 p -> 빛 으로 가다가 다른 물체와 닿을 경우 : vis 값은 false 가됨
	//			: vis 가 false 일 경우 무조건 그림자가 되는게 아니다.
	//				물체 빛 물체 순서일 경우 거리 값을 계산해봐야함 -> t > len
	//				이 거리값이 len 보다 클 경우 처음 p 는 색을 가진다.!
	//	 p -> 빛 으로 가다가 다른 물체와 닿지 않을 경우 : vis 값은 true 가됨

// color = vis * light intensity * light color * facing Ratio

static	t_rgb_f calc_color(t_rt *rt_info, t_l *light_source, t_phit *obj_info)
{
	t_ray	shadow_ray;
	t_rgb_f	final_color;
	t_rgb_f	light_color;
	t_rgb_f	specluar_color;

	double	t;
	double	facing_ratio;
	int		vis;
	double	len;

	t_phit	nothing;
	t_obj_count nothing1;


	shadow_ray.direction_ = subtract(&(light_source->vec_), &(obj_info->hit_point));
	len = vector_len(&(shadow_ray.direction_));
	shadow_ray.direction_ = normalize(&(shadow_ray.direction_));
	shadow_ray.origin_ = multiply(&(obj_info->hit_normal), 0.1);
	shadow_ray.origin_ = add(&(obj_info->hit_point), &(shadow_ray.origin_));
	t = t_infinity;
	facing_ratio = 0;
	vis = !intersection_controller(rt_info, &shadow_ray, &nothing, &t, &nothing1);
	// intersec - false : 충돌 X -> vis 1
	// intersec - true  : 충돌 O -> vis 0
	// final_color = init_color(0);
	if (vis || t > len) // 그림자 x
		facing_ratio = fmax(0.0, dot_product(&(obj_info->hit_normal), &(shadow_ray.direction_)));

	light_color = multi_colorf(&(light_source->rgb_), light_source->light_);
	final_color = colorf_multi_colorf(&(light_color), &(obj_info->colorf));
	// if (final_color.r_ < 0 || final_color.g_ < 0 || final_color.b_ < 0)
	// 	printf("|%f\t%f\t%f|\t", final_color.r_, final_color.g_, final_color.b_);
	final_color = multi_colorf(&final_color, facing_ratio);

	// if (final_color.r_ < 0 || final_color.g_ < 0 || final_color.b_ < 0)
		// printf("|%f\t%f\t%f|\t", final_color.r_, final_color.g_, final_color.b_);
	// specular
	if (facing_ratio)
	{
		specluar_color = calc_specular(&shadow_ray, obj_info, &light_color);
		// specluar_color =  multi_colorf(&specluar_color, vis);
		// printf("%f\t", specluar_color.r_ + specluar_color.g_ + specluar_color.b_);
		final_color = add_color(&final_color, &specluar_color);
	}
	return (final_color);
}

int			pixel_shader(t_rt *rt_info, t_ray *camera_ray, double *t, t_phit *obj_info)
{
	t_list	*cur_light_node;
	t_rgb_f	calc_result;
	t_rgb_f ambient_color;
	t_rgb_f	color;

	obj_info->hit_point = calc_hit_point(camera_ray, t);
	calc_normal(obj_info, camera_ray);
	obj_info->cam_ray = camera_ray;
	color = init_color(0.0);
	while (isempty_node(rt_info->lst_pos.cur_l))
	{
		cur_light_node = get_node(&(rt_info->lst_pos.cur_l));
		calc_result = calc_color(rt_info, (t_l*)(cur_light_node->content), obj_info);
	// if (calc_result.r_ < 0 || calc_result.g_ < 0 || calc_result.b_ < 0)
	// 	printf("|%f\t%f\t%f|\t", calc_result.r_, calc_result.g_, calc_result.b_);
		color = add_color(&color, &calc_result);
	}
	reset_light_pos(&(rt_info->lst_pos), rt_info->count_);
	// ambient 계산
	ambient_color =	multi_colorf(&(rt_info->t_a_->rgb_), rt_info->t_a_->light_);
	// ambient_color = colorf_multi_colorf(&(rt_info->t_a_->rgb_), &(obj_info->colorf));
	ambient_color = colorf_multi_colorf(&(ambient_color), &(obj_info->colorf));
	color = add_color(&color, &ambient_color);
	if (color.r_ < 0 || color.g_ < 0 || color.b_ < 0)
		printf("|%f\t%f\t%f|\t", color.r_, color.g_, color.b_);

	
	// t_union_color	color_int;
	int r = color.r_ * 256;
	int g = color.g_ * 256;
	int b = color.b_ * 256;
	// printf("|%d\t%d\t%d|\t", r, g, b);
	// color_int.color_array[2] = r;
	// color_int.color_array[1] = g;
	// color_int.color_array[0] = b;

	int color_a = 	65536 * r + 256 * g + b;
	// return (color_int.combination);
	// int  a;
	// a = change_type_colorf_to_int(&color);
	// if (color_int.combination < 0)
	// printf("%d", color_int.combination);
	// return (color_int.combination);
	return (color_a);
}
