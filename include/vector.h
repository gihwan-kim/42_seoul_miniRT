/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:07:11 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/05/19 17:50:37 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "mini_rt.h"

typedef struct	s_matrix
{
	double d[4][4];
}				t_matrix;

t_vec	multiply_by_matrix(t_vec p, t_matrix m);
t_vec	*new_vector(double x, double y, double z);



#endif