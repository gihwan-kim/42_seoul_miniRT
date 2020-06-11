/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 09:48:34 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/11 20:15:52 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H
# define BIT_PER_PIXEL 24
# define BIT_MAP_INFO_HEADER_SIZE 40
# define BIT_MAP_FILE_HEADER_SIZE 14
# define BIT_MAP_HEADER_SIZE 54
# define BIT_PALNE 1
# include "mini_rt.h"

void	bmp(int width, int height, t_rgb **data);
t_rgb	**create_bmp(int width, int height);
void	free_bmp(t_rgb **bmp, int height);

#endif
