/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:54:27 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/06/10 22:11:08 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "mini_rt.h"

int		print_error(int errno, char *comment, t_rt *rt_info);
int		print_error_comment(char *comment, t_rt *rt_info);
int		print_error_nofree(int errno, char *comment);
void	rt_info_free(t_rt *rt_info);
#endif
