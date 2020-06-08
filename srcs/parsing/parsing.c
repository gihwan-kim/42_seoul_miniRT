/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:26 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/07 13:03:52 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_identifier(char **split, t_rt *rt_info)
{
	size_t len;
	(void)rt_info;
	len = (ft_strlen(split[0]) > 1) ? ft_strlen(split[0]) : 1;
	if (!ft_strncmp(split[0], "R", len))
		parsing_resolution(split, rt_info);
	else if(!ft_strncmp(split[0], "A", len))
		parsing_ambient(split, rt_info);
	else if(!ft_strncmp(split[0], "c", len))
		parsing_camera(split, rt_info);
	else if(!ft_strncmp(split[0], "l", len))
		parsing_light(split, rt_info);
	else if(!ft_strncmp(split[0], "sp", len))
		parsing_sphere(split, rt_info);
	else if(!ft_strncmp(split[0], "pl", len))
		parsing_plane(split, rt_info);
	else if(!ft_strncmp(split[0], "cy", len))
		parsing_cylinder(split, rt_info);
	else if(!ft_strncmp(split[0], "tr", len))
		parsing_triangle(split, rt_info);
	else if(!ft_strncmp(split[0], "sq", len))
		parsing_square(split, rt_info);
	else
		return (print_error(22, "Element format is worng!\n", rt_info));
	return (SUCCESS);
}

static void	check_line(char *line, t_rt *rt_info)
{
	char **split;

	if (*line)
	{
		split = ft_split(line, ' ');
		check_identifier(split, rt_info);
	}
	free(line);
}

static void	set_lst_position(t_rt *rt_info)
{
	rt_info->lst_pos.cur_sp = rt_info->lst_sp_;
	rt_info->lst_pos.cur_pl = rt_info->lst_pl_;
	rt_info->lst_pos.cur_sq = rt_info->lst_sq_;
	rt_info->lst_pos.cur_cy = rt_info->lst_cy_;
	rt_info->lst_pos.cur_tr = rt_info->lst_tr_;
	rt_info->lst_pos.cur_c = rt_info->lst_c_;
	rt_info->lst_pos.cur_l = rt_info->lst_l_;
	rt_info->lst_pos.fst_sp = rt_info->lst_sp_;
	rt_info->lst_pos.fst_pl = rt_info->lst_pl_;
	rt_info->lst_pos.fst_sq = rt_info->lst_sq_;
	rt_info->lst_pos.fst_cy = rt_info->lst_cy_;
	rt_info->lst_pos.fst_tr = rt_info->lst_tr_;
	rt_info->lst_pos.fst_c = rt_info->lst_c_;
	rt_info->lst_pos.fst_l = rt_info->lst_l_;
}

int			parsing_rt_file(char *file, t_rt *rt_info)
{
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
		check_line(line, rt_info);
	check_line(line, rt_info);
	set_lst_position(rt_info);
	rt_info->count_->all_obj = get_all_object_count(rt_info);
	return (SUCCESS);
}