/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:50:38 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/14 14:05:27 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "mini_rt.h"

int	print_error_int(char* comment)
{
	ft_putstr_fd(comment, 1);
	return (ERROR);
}

void *print_error_ptr(char *comment)
{
	ft_putstr_fd(comment, 1);
	return (NULL);
}