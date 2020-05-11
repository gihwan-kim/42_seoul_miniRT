/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 15:10:55 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:33:09 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the last element of the list.
*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list *temp;
	t_list *last;

	temp = lst;
	last = temp;
	while (temp)
	{
		last = temp;
		temp = temp->next;
	}
	return (last);
}
