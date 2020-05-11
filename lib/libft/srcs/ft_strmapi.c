/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 13:27:27 by gihkim            #+#    #+#             */
/*   Updated: 2020/04/09 11:31:52 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result_strmapi;
	int		i;

	i = 0;
	if (!(result_strmapi = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (result_strmapi);
	while (s[i])
	{
		result_strmapi[i] = (*f)(i, s[i]);
		i++;
	}
	result_strmapi[i] = '\0';
	return (result_strmapi);
}
