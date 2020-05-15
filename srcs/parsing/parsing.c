/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:26 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/15 09:53:45 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_identifier(char **split, t_rt *rt_info)
{
	size_t len;
	(void)rt_info;
	len = (ft_strlen(split[0]) > 1) ? ft_strlen(split[0]) : 1;
	printf("identifier : |%s|\n", split[0]);
	if (!ft_strncmp(split[0], "R", len))
		parsing_resolution(split, rt_info);
	else if(!ft_strncmp(split[0], "A", len))
		parsing_ambient(split, rt_info);
	else if(!ft_strncmp(split[0], "c", len))
		parsing_camera(split, rt_info);
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
		return (print_error("Element format is worng!\n"));
	return (SUCCESS);
}

int parsing_rt_file(char *file, t_rt *rt_info)
{
	char **split;
	char *line;
	int fd;
	int ret;

	line = NULL;
	fd = open(file, O_RDONLY);
	if (!(rt_info->count_ =ft_calloc(sizeof(t_count), 1)))
		return (SUCCESS);
	if (fd == -1)
		return (ERROR);
	while((ret = get_next_line(fd, &line) > 0))
	{
		if (*line)
		{
			split = ft_split(line, ' ');
			check_identifier(split, rt_info);
		}
		free(line);
		//free split
	}
	return (SUCCESS);
}