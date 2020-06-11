/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:08:55 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/11 20:13:06 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

t_rgb	**create_bmp(int width, int height)
{
	t_rgb	**result;
	int		i;

	i = 0;
	result = malloc(sizeof(t_rgb*) * height);
	while (i < height)
	{
		result[i] = malloc(sizeof(t_rgb) * width);
		i++;
	}
	return (result);
}

void	free_bmp(t_rgb **bmp, int height)
{
	int i;

	i = -1;
	while (++i < height)
		free(bmp[i]);
	free(bmp);
}
