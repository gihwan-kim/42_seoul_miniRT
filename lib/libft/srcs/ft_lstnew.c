/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 15:02:48 by gihkim            #+#    #+#             */
/*   Updated: 2020/06/11 20:35:49 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** content :  The content to create the new element with
** Allocates (with malloc(3)) and returns a new
** element. The variable ’content’ is initialized
** with the value of the parameter ’content’. The
** variable ’next’ is initialized to NULL.
** <t_list>			<t_list>		<t_list>
** ---------		---------		---------
** |content|		|content|		|content|
** |next---|------> |next---|------>|next---|--- > NULL
** ---------		---------		---------
*/

t_list	*ft_lstnew(void *content)
{
	t_list *list_ptr;

	if (!(list_ptr = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	list_ptr->content = content;
	list_ptr->next = NULL;
	return (list_ptr);
}
