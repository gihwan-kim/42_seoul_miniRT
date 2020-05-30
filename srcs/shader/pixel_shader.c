/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:09:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/30 15:36:52 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

/*
** hit_n is orthogonal to hit point
** normal 은 물체 반대방향을 가리키면안됨
** camera 쪽을 바라봐야함
** camera_ray direction 과 normal 의 각은 둔각이 되어야한다.
*/
static void	calc_normal(t_rt *rt_info,
						t_vec *hit_p,
						t_vec *hit_n,
						t_ray *ray)
{
	t_e_obj hit_obj_type;
	void	*obj;

	hit_obj_type = rt_info->img_.hit_obj.type;
	obj = rt_info->img_.hit_obj.obj;
	if (hit_obj_type = plane)
		make_plane_normal((t_pl*)plane, hit_n, hit_p);
	else if (hit_obj_type = sphere)
		make_sphere_normal((t_sp*)sphere, hit_n, hit_p);
	else if (hit_obj_type = cylinder)
		make_cylinder_normal((t_cy*)cylinder, hit_n, hit_p);
	else if (hit_obj_type = square)
		make_square_normal((t_sq*)square, hit_n, hit_p);
	else if (hit_obj_type = triangle)
		make_triangle_normal((t_tr*)triangle, hit_n, hit_p);
	if (dot_product(hit_n, &(ray->direction_)) > 0)
		vec_inverse(hit_n);
}

/*
** light_dir  : camera ray 와 물체가 충돌한 지점 -> 광원까지 방향벡터
** shadow_ray
**	 : 충돌지점->광원 벡터
**	 : shadow 를 만드는데 사용 -> intersection_controller 함수 사용하여 확인
** facing Ratio : 
**	 : n ● v
**	 : n - hit_point 를 지나는 접선의 수직인 벡터
**	 : v - hit_point -> 광원 방향인 normal 벡터
**	 : n ● v 의 값에 따라 그 점의 밝기가 달라진다.
** vis
**	 : shadow 유뮤, intersection_controller 가 ture 이면 shadow 가 있다고 판단한다.
**	 : vis 가 true 일 경우 color 에 곱할때 값은 변하지 않을 것이다.
** bias
**	 : Shadow-Acne: Avoiding Self-Intersection
*/

// color = vis * light intensity * light color * facing Ratio
static	int calc_color(t_rt *rt_info, 
						t_l *light_source,
						t_vec *hit_point,
						t_vec *hit_n)
{
	// light source
	t_vec	light_dir;
	t_ray	shadow_ray;

	/// color
	int		color;
	double	t;
	double	facing_ratio;
	t_rgb_f	light_intensity;
	int		vis;
	double	bias;
	double	len;

	light_dir = subtract(&(light_source->vec_), hit_point);
	len = vector_len(&light_dir);
	light_dir = normalize(&light_dir);
	shadow_ray.direction_ = light_dir;
	shadow_ray.direction_ = normalize(&shadow_ray.direction_);
	shadow_ray.origin_ = light_source->vec_;
	facing_ratio = fmax(0.0, dot_product(hit_n, &light_dir));
	t = t_infinity;
	calc_light_amount(light_source, &light_intensity);
	vis = !intersection_controller(rt_info, &shadow_ray, &t);

	// vis true or len 보다 t 가 더 클 경우 -> shadow 가 없거나 
	// p -> 빛 으로 가다가 다른 물체와 닿을 경우 : vis 값은 false 가됨
	//		: vis 가 false 일 경우 무조건 그림자가 되는게 아니다.
	//			물체 빛 물체 순서일 경우 거리 값을 계산해봐야함 -> t > len
	//			이 거리값이 len 보다 클 경우 처음 p 는 색을 가진다.!
	// p -> 빛 으로 가다가 다른 물체와 닿지 않을 경우 : vis 값은 true 가됨
	if (vis || t > len)
	{

	}

	return (color);
}

int			pixel_shader(t_rt *rt_info, t_ray *camera_ray, double *t)
{
	t_vec	hit_point;
	t_vec	hit_normal;
	t_vec	p_dot_d;
	t_list	*cur_light_node;
	int		color;


	p_dot_d = multiply(&(camera_ray->direction_), *t);
	hit_point = add(&(camera_ray->origin_), &p_dot_d);
	calc_normal(rt_info, &hit_point, &hit_normal, camera_ray);
	while (cur_light_node = get_node(rt_info->lst_pos.cur_l))
	{
		color += calc_color(rt_info, (t_l*)(cur_light_node->content),
							&hit_point, &hit_normal);
	}
	return (color);
}
