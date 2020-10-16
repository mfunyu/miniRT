/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_2dvec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:57:24 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/05 14:34:35 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

double	dot_p_2d(double v1[3], double v2[3], int index1, int index2)
{
	return (v1[index1] * v2[index1] + v1[index2] * v2[index2]);
}

double	len_2d_vec(double vec[3], double index1, double index2)
{
	return (sqrt(dot_p_2d(vec, vec, index1, index2)));
}
