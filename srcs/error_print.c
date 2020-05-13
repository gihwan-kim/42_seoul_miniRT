/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:50:38 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/13 12:19:39 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "mini_rt.h"

int	print_error(char* comment)
{
	ft_putstr_fd(comment, 1);
	return (FALSE);
}