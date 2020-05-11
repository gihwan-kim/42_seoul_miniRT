/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 15:14:39 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:33:06 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** make new_list : new_list have to make first node
** (new_list dosen't have node not yet)
** result(return) of f function is new_list of node
** new_list : node - node - node ...
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_lst;
	t_list *new_node;

	if (!lst || !f)
		return (NULL);
	if (!(new_node = ft_lstnew(f(lst->content))))
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	new_lst = new_node;
	lst = lst->next;
	while (lst)
	{
		if (!(new_node = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&new_lst, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&new_lst, new_node);
	}
	return (new_lst);
}
