/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 15:02:48 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:33:03 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *list_ptr;

	if (!(list_ptr = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	list_ptr->content = content;
	list_ptr->next = NULL;
	return (list_ptr);
}
