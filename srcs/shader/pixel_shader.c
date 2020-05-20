/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:09:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/19 11:44:06 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"


t_vec	make_ray(t_rt *rt_info)
{
	t_vec	ray;

}

int		pixel_shader(t_rt *rt_info)
{
	int	pixel_color;
	int ambient; // 원래 object 색깔
	int diffuse; // 난반사광
	int specular; // 정반사광


	pixel_color = ambient + diffuse + specular ;
	return (pixel_color);
}
