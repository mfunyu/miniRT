/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 00:26:31 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/01 19:45:08 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include "cylinder.h"

/*
** rotation z-axis
** 	[cos, -sin, 0][X]
** 	[sin,  cos, 0][Y]
** 	[  0,    0, 1][Z]
*/

void	rotate_z(double new[3], double cosz, int sign)
{
	double	copy[3];
	double	sinz;

	set_vec(copy, new);
	sinz = sqrt(1 - pow(cosz, 2));
	new[X] = cosz * copy[X] - sign * sinz * copy[Y];
	new[Y] = sign * sinz * copy[X] + cosz * copy[Y];
	new[Z] = copy[Z];
}

/*
** rotation x-axis
** 	[ 1,   0,    0][X]
** 	[ 0, cos, -sin][Y]
** 	[ 0, sin,  cos][Z]
*/

void	rotate_x(double new[3], double cosx, int sign)
{
	double	copy[3];
	double	sinx;

	set_vec(copy, new);
	sinx = sqrt(1 - pow(cosx, 2));
	new[X] = copy[X];
	new[Y] = cosx * copy[Y] - sign * sinx * copy[Z];
	new[Z] = sign * sinx * copy[Y] + cosx * copy[Z];
}

void	rotate(double centerline[3], double set[3], int sign)
{
	double	y0[3];
	double	cosz;
	double	cosx;

	y0[X] = 0;
	y0[Y] = 1;
	y0[Z] = 0;
	if (!centerline[X] && !centerline[Z])
		return ;
	if (centerline[X])
	{
		if (centerline[X] < 0)
			vec_multi(centerline, -1);
		cosz = dot_p_2d(centerline, y0, X, Y) / len_2d_vec(centerline, X, Y);
		rotate_z(set, cosz, sign);
	}
	if (centerline[Z])
	{
		if (centerline[Z] > 0)
			vec_multi(centerline, -1);
		cosx = dot_p_2d(centerline, y0, Y, Z) / len_2d_vec(centerline, Y, Z);
		rotate_x(set, cosx, sign);
	}
}
