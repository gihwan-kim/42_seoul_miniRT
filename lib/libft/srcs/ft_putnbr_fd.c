/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 17:36:51 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:32:20 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive(int nb, char *boundary, int fd)
{
	if (nb < 10)
		write(fd, boundary + nb, 1);
	else
	{
		recursive(nb / 10, boundary, fd);
		recursive(nb % 10, boundary, fd);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	char *boundary;

	boundary = "0123456789";
	if (n >= 0)
		recursive(n, boundary, fd);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		write(fd, "-", 1);
		recursive(-n, boundary, fd);
	}
}
