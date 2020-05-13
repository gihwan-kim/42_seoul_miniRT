/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:26 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/14 00:23:22 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	check_identifier(char **split)
{
	size_t len;

	len = ft_strlen(split[0] > 1) ? ft_strlen(split[0]) : 1;
	if (ft_strncmp(split[0], "R", len))
		;
	else if(ft_strncmp(split[0], "A", len))
		;
	else if(ft_strncmp(split[0], "c", len))
		;
	else if(ft_strncmp(split[0], "l", len))
		;
	else if(!ft_strncmp(split[0], "sp", len))
		;
	else if(!ft_strncmp(split[0], "pl", len))
		;
	else if(!ft_strncmp(split[0], "cy", len))
		;
	else if(!ft_strncmp(split[0], "tr", len))
		;
	else if(!ft_strncmp(split[0], "sp", len))
		;
	else
		return (ERROR);
}

int parsing_rt_file(char *file)
{
	char **split;
	char *line;
	int fd;
	int ret;

	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	while((ret = get_next_line(fd, &line) > 0))
	{
		split = ft_split(line, ' ');
		free(line);
	}
	return (1);
}