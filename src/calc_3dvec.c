/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_3dvec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:57:24 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/18 19:50:02 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot_p(double *p1, double *p2)
{
	return (p1[X] * p2[X] + p1[Y] * p2[Y] + p1[Z] * p2[Z]);
}

void	cross_p(double dest[3], double a[3], double b[3])
{
	dest[X] = a[Y] * b[Z] - a[Z] * b[Y];
	dest[Y] = a[Z] * b[X] - a[X] * b[Z];
	dest[Z] = a[X] * b[Y] - a[Y] * b[X];
}

void	vec_add(double dst[3], double *v1, double *v2)
{
	int		k;

	k = 0;
	while (k < 3)
	{
		dst[k] = v2[k] + v1[k];
		k++;
	}
}

void	vec_sub(double dst[3], double *v1, double *v2)
{
	int		k;

	k = 0;
	while (k < 3)
	{
		dst[k] = v2[k] - v1[k];
		k++;
	}
}

void	vec_multi(double dst[3], double val)
{
	int		k;

	k = 0;
	while (k < 3)
	{
		dst[k] *= val;
		k++;
	}
}
