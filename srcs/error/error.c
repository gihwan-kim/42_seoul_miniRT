/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:50:38 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 20:28:09 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	rt_info_free(t_rt *rt_info)
{
	free(rt_info->t_r_);
	free(rt_info->t_a_);
	free(rt_info->count_);
	ft_lstclear(&(rt_info->lst_pos.fst_sp), free);
	ft_lstclear(&(rt_info->lst_pos.fst_pl), free);
	ft_lstclear(&(rt_info->lst_pos.fst_sq), free);
	ft_lstclear(&(rt_info->lst_pos.fst_cy), free);
	ft_lstclear(&(rt_info->lst_pos.fst_tr), free);
	ft_lstclear(&(rt_info->lst_pos.fst_c), free);
	ft_lstclear(&(rt_info->lst_pos.fst_l), free);
	free(rt_info);
}

int		print_error(int errno, char *comment, t_rt *rt_info)
{
	ft_putstr_fd("Error\n", 1);
	ft_putendl_fd(strerror(errno), 1);
	ft_putendl_fd(comment, 1);
	rt_info_free(rt_info);
	return (ERROR);
}

int		print_error_comment(char *comment, t_rt *rt_info)
{
	ft_putstr_fd("Error\n", 1);
	ft_putendl_fd(comment, 1);
	rt_info_free(rt_info);
	return (ERROR);
}

int		print_error_no(int errno, t_rt *rt_info)
{
	ft_putstr_fd("Error\n", 1);
	ft_putendl_fd(strerror(errno), 1);
	rt_info_free(rt_info);
	return (ERROR);
}

int		print_error_nofree(int errno, char *comment)
{
	ft_putstr_fd("Error\n", 1);
	ft_putendl_fd(strerror(errno), 1);
	ft_putendl_fd(comment, 1);
	return (ERROR);
}
