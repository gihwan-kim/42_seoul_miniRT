/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:50:38 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/11 16:26:31 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "mini_rt.h"

int	print_error(int no)
{
	if (no == 1)
		write(1, "No argument!\n", 14);
	else if (no == 2)
		write(1, "Argument number must be 2 or 3!\n", 33);
	else if (no == 3)
		write(1, "Second argument is wrong format!\n", 35);
	return (FALSE);
}