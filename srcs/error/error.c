/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:50:38 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/23 15:55:25 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	rt_info_free(t_rt *rt_info)
{
	free(rt_info->t_r_);
	free(rt_info->t_a_);
	free(rt_info->count_);

	ft_lstclear(rt_info->lst_sp, free);
	ft_lstclear(rt_info->lst_pl, free);
	ft_lstclear(rt_info->lst_sq, free);
	ft_lstclear(rt_info->lst_cy, free);
	ft_lstclear(rt_info->lst_tr_, free);
	ft_lstclear(rt_info->lst_c_, free);
	ft_lstclear(rt_info->lst_l_, free);
}

int	print_error(char* comment, t_rt *rt_info)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(comment, 1);
	rt_info_free(rt_info);
	return (ERROR);
}
