/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:30:00 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/14 17:21:54 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "mini_rt.h"
size_t	get_argument_count(char **split);
int parsing_rt_file(char *file, t_rt *rt_info);
int	check_str_isdigit(const char *str);
double	ft_atof(const char *str);
t_a *parsing_ambient(char **split, t_rt *rt_info);
t_r	*parsing_resolution(char **split, t_rt *rt_info);

#endif