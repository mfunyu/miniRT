/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 21:05:07 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/21 22:01:45 by mfunyu           ###   ########.fr       */
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

double	calc_triangle(double dir[3], double orig[3], t_tr tr)
{
	double	ab[3];
	double	ac[3];
	double	normal[3];
	double	t;

	vec_sub(ab, tr.coord1, tr.coord2);
	vec_sub(ac, tr.coord1, tr.coord3);
	cross_p(normal, ab, ac);
	normalize(normal);
	t = calc_plane(orig, tr.coord1, normal, dir);
	if (t < EPSILON)
		return (-1);
	int k = 0;
	double p[3];
	while (k < 3)
	{
		p[k] = orig[k] + t * dir[k];
		k++;
	}
	double bc[3];
	double ca[3];
	double vp[3];
	double test[3];
	vec_sub(vp, tr.coord1, p);
	cross_p(test, ab, vp);
	if (dot_p(test, normal) < 0)
		return (-1);
	vec_sub(bc, tr.coord2, tr.coord3);
	vec_sub(vp, tr.coord2, p);
	cross_p(test, bc, vp);
	if (dot_p(test, normal) < 0)
		return (-1);
	vec_sub(ca, tr.coord3, tr.coord1);
	vec_sub(vp, tr.coord3, p);
	cross_p(test, ca, vp);
	if (dot_p(test, normal) < 0)
		return (-1);
	return (t);
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
	set_triangle_normal(elem->tr[index], info->n);
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
