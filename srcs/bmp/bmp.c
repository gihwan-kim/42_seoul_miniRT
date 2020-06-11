/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 09:47:05 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/11 20:32:01 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

static void	init_bmp(int width, int height, unsigned char *header)
{
	int padding;
	int image_size;
	int file_size;

	padding = (4 - ((width * sizeof(t_rgb)) % 4)) % 4;
	image_size = ((width * sizeof(t_rgb)) + padding) * height;
	file_size = BIT_MAP_HEADER_SIZE + image_size;
	header[0] = 'B';
	header[1] = 'M';
	header[2] = file_size;
	header[10] = BIT_MAP_HEADER_SIZE;
	header[14] = BIT_MAP_INFO_HEADER_SIZE;
	*(unsigned int *)(&header[18]) = width;
	*(unsigned int *)(&header[22]) = height;
	header[26] = BIT_PALNE;
	header[28] = BIT_PER_PIXEL;
	header[34] = image_size;
}

void		bmp(int width, int height, t_rgb **data)
{
	unsigned char	*header;
	unsigned char	padding_color[3];
	int				padding;
	int				loop;
	int				fd;

	header = ft_calloc(sizeof(unsigned char), BIT_MAP_HEADER_SIZE);
	init_bmp(width, height, header);
	fd = open("miniRT.bmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	loop = height;
	padding = (4 - ((width * sizeof(t_rgb)) % 4)) % 4;
	padding_color[0] = 0;
	padding_color[1] = 0;
	padding_color[2] = 0;
	write(fd, header, BIT_MAP_HEADER_SIZE);
	while (loop >= 0)
	{
		write(fd, data[loop], width * sizeof(t_rgb));
		if (padding > 0)
			write(fd, padding_color, padding);
		loop--;
	}
	close(fd);
	free(header);
	free_bmp(data, height);
}
