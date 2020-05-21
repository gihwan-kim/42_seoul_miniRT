/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_shader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:07:07 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/21 15:14:15 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_SHADER_H
# define VERTEX_SHADER_H

#include "mini_rt.h"

t_c			*get_camera(t_rt *rt_info);
t_matrix	lookAt(const t_c *camera);
t_ray		make_camera_ray(int x, int y, t_matrix *c2w, t_rt *rt_info, t_c *camera);
#endif