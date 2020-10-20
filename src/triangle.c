/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 21:05:07 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/20 23:10:36 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

void	set_triangle_normal(t_tr tr, double normal[3])
{
	double	ab[3];
	double	ac[3];

	vec_sub(ab, tr.coord1, tr.coord2);
	vec_sub(ac, tr.coord1, tr.coord3);
	cross_p(normal, ab, ac);
	normalize(normal);
}

bool	is_intersect_inside_tr(t_tr tr, double p[3], double normal[3])
{
	double	ab[3];
	double	bc[3];
	double	ca[3];
	double	coord_to_p[3];
	double	check[3];

	vec_sub(coord_to_p, tr.coord1, p);
	cross_p(check, ab, coord_to_p);
	if (dot_p(check, normal) < 0)
		return (false);
	vec_sub(bc, tr.coord2, tr.coord3);
	vec_sub(coord_to_p, tr.coord2, p);
	cross_p(check, bc, coord_to_p);
	if (dot_p(check, normal) < 0)
		return (false);
	vec_sub(ca, tr.coord3, tr.coord1);
	vec_sub(coord_to_p, tr.coord3, p);
	cross_p(check, ca, coord_to_p);
	if (dot_p(check, normal) < 0)
		return (false);
	return (true);
}

double	calc_triangle(double dir[3], double orig[3], t_tr tr)
{
	double	normal[3];
	double	p[3];
	double	t;
	int		k;

	set_triangle_normal(tr, normal);
	t = calc_plane(orig, tr.coord1, normal, dir);
	if (t < EPSILON)
		return (-1);
	k = 0;
	while (k < 3)
	{
		p[k] = orig[k] + t * dir[k];
		k++;
	}
	if (is_intersect_inside_tr(tr, p, normal))
		return (t);
	return (-1);
}

void	set_triangle(t_c camera, t_info *info, t_elem *elem, int index)
{
	double	t;

	t = calc_triangle(info->dc, camera.coord, elem->tr[index]);
	if (t < 0 || !(info->index == -1 || info->t > t))
		return ;
	info->type = TRIANGLE;
	info->index = index;
	info->t = t;
	set_vec(info->rgb, elem->tr[index].rgb);
	set_pvec(info->p, camera.coord, info->dc, t);
	set_triangle_normal(elem->tr[index], info->p);
	adjust_normal_vec(info->n, camera.coord, info->p);
}

int		is_behind_tr(t_elem *elem, double intersect[3], double direction[3])
{
	double	t;
	int		i;

	i = 0;
	while (elem->tr[i].exist)
	{
		t = calc_triangle(direction, intersect, elem->tr[i]);
		if (t >= 0 && is_closer(direction, t))
			break ;
		i++;
	}
	if (elem->tr[i].exist)
		return (1);
	return (0);
}
