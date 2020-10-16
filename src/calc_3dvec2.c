/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_3dvec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:16:27 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/22 20:30:00 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "output.h"

void	normalize(double vec[3])
{
	double	len;
	int		k;

	len = sqrt(dot_p(vec, vec));
	k = 0;
	while (k < 3)
	{
		vec[k] /= len;
		k++;
	}
}

void	set_vec(double dst[3], double src[3])
{
	int		k;

	k = 0;
	while (k < 3)
	{
		dst[k] = src[k];
		k++;
	}
}

void	set_pvec(double pvec[3], double position[3],
					double direction[3], double length)
{
	int		k;

	k = 0;
	while (k < 3)
	{
		pvec[k] = position[k] + (direction[k] * length);
		k++;
	}
}

double	is_closer(double d[3], double t)
{
	double	copy[3];

	set_vec(copy, d);
	vec_multi(copy, t);
	if (sqrt(dot_p(d, d)) > sqrt(dot_p(copy, copy)))
		return (1);
	return (0);
}

void	adjust_normal_vec(double n[3], double origin[3], double dest[3])
{
	double	direction[3];

	vec_sub(direction, dest, origin);
	if (dot_p(direction, n) < 0)
		vec_multi(n, -1);
	normalize(n);
}
