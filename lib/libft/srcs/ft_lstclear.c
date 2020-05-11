/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 15:26:55 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:33:19 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Deletes and frees the given element and every successor of that element,
** using the function del and free .Finally, the pointer
** to the list must be set to NUL
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *temp;
	t_list *temp_next;

	temp = (*lst)->next;
	while (temp)
	{
		del(temp->content);
		temp_next = temp->next;
		free(temp);
		temp = temp_next;
	}
	ft_lstdelone(*lst, del);
	*lst = NULL;
}
