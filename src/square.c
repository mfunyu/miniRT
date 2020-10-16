/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:40:19 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/23 15:20:24 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include "minirt.h"

void	calc_local_axc(t_sq *sq, double x[3], double y[3])
{
	double	base[3];

	base[X] = 0;
	base[Y] = 0;
	base[Z] = 0;
	if (sq->n[Z] || sq->n[X])
		base[Y] = 1;
	else
		base[Z] = 1;
	cross_p(x, base, sq->n);
	cross_p(y, sq->n, x);
	normalize(x);
	normalize(y);
}

void	find_coord(t_tr *tr, t_sq *sq, double ret[3])
{
	double	x[3];
	double	y[3];
	double	half;
	int		k;

	calc_local_axc(sq, x, y);
	half = sq->size / 2;
	k = 0;
	while (k < 3)
	{
		tr->coord2[k] = sq->center[k] + half * x[k] + half * y[k];
		tr->coord3[k] = sq->center[k] - half * x[k] - half * y[k];
		tr->coord1[k] = sq->center[k] + half * x[k] - half * y[k];
		ret[k] = sq->center[k] - half * x[k] + half * y[k];
		k++;
	}
}

/*
** find the coordinates
*/

double	calc_square(double origin[3], double d[3], t_sq sq)
{
	t_tr	tr;
	double	anothercoord[3];
	double	t;

	if ((t = calc_plane(origin, sq.center, sq.n, d)) <= 0)
		return (-1);
	find_coord(&tr, &sq, anothercoord);
	if ((t = calc_triangle(d, origin, tr)) >= 0)
		return (t);
	set_vec(tr.coord1, anothercoord);
	if ((t = calc_triangle(d, origin, tr)) >= 0)
		return (t);
	return (-1);
}

void	set_square(t_c camera, t_info *info, t_elem *elem, int index)
{
	double	t;

	t = calc_square(camera.coord, info->dc, elem->sq[index]);
	if (t < 0 || !(info->index == -1 || info->t > t))
		return ;
	info->type = SQUARE;
	info->index = index;
	info->t = t;
	set_vec(info->rgb, elem->sq[index].rgb);
	set_pvec(info->p, camera.coord, info->dc, t);
	set_vec(info->n, elem->sq[index].n);
	adjust_normal_vec(info->n, camera.coord, info->p);
}

int		is_behind_sq(t_info *info, t_elem *elem, int index)
{
	double	direction[3];
	double	t;
	int		i;

	i = 0;
	while (elem->sq[i].exist)
	{
		if (info->type == SQUARE && info->index == i)
		{
			i++;
			continue;
		}
		vec_sub(direction, info->p, elem->l[index].coord);
		t = calc_square(info->p, direction, elem->sq[i]);
		if (t >= 0 && is_closer(direction, t))
			break ;
		i++;
	}
	if (elem->sq[i].exist)
		return (1);
	return (0);
}
