/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:28:20 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/20 12:39:51 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

double	calc_plane(double origin[3], double coord[3],
			double n[3], double d[3])
{
	double	sub[3];
	double	t;

	vec_sub(sub, coord, origin);
	if (dot_p(d, n) != 0)
	{
		if ((t = -dot_p(sub, n) / dot_p(d, n)) > 0)
			return (t);
	}
	return (-1);
}

void	set_plane(t_c camera, t_info *info, t_elem *elem, int index)
{
	double	t;

	t = calc_plane(camera.coord, elem->pl[index].coord,
					elem->pl[index].n, info->dc);
	if (t < 0 || !(info->index == -1 || info->t > t))
		return ;
	info->type = PLANE;
	info->index = index;
	info->t = t;
	set_vec(info->rgb, elem->pl[index].rgb);
	set_pvec(info->p, camera.coord, info->dc, t);
	set_vec(info->n, elem->pl[index].n);
	adjust_normal_vec(info->n, camera.coord, info->p);
}

int		is_behind_pl(t_elem *elem, double intersect[3], double direction[3])
{
	double	t;
	int		i;

	i = 0;
	while (elem->pl[i].exist)
	{
		t = calc_plane(intersect, elem->pl[i].coord, elem->pl[i].n, direction);
		if (t > 0 && is_closer(direction, t))
			break ;
		i++;
	}
	if (elem->pl[i].exist)
		return (1);
	return (0);
}
