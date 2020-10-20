/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 21:05:07 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/20 12:36:12 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

double	calc_ab(double e1[3], double e2[3], double r[3], double d[3])
{
	double	alpha[3];
	double	beta[3];
	double	denominator;
	double	u;
	double	v;

	cross_p(alpha, d, e2);
	cross_p(beta, r, e1);
	denominator = dot_p(e1, alpha);
	if (-EPSILON < denominator && denominator < EPSILON)
		return (-1);
	u = dot_p(alpha, r) / denominator;
	if (u < 0 || u > 1)
		return (-1);
	v = dot_p(d, beta) / denominator;
	if (v < 0 || v > 1 || v + u > 1)
		return (-1);
	return (dot_p(e2, beta) / denominator);
}

double	calc_triangle(double d[3], double s[3], t_tr tr)
{
	double	e1[3];
	double	e2[3];
	double	r[3];
	double	t;

	vec_sub(e1, tr.coord1, tr.coord2);
	vec_sub(e2, tr.coord1, tr.coord3);
	vec_sub(r, tr.coord1, s);
	t = calc_ab(e1, e2, r, d);
	if (t >= 0)
		return (t);
	vec_sub(e1, tr.coord3, tr.coord1);
	vec_sub(e2, tr.coord3, tr.coord2);
	vec_sub(r, tr.coord3, s);
	return (calc_ab(e1, e2, r, d));
}

void	set_triangle_normal(t_tr tr, t_info *info)
{
	double	ab[3];
	double	ac[3];

	vec_sub(ab, tr.coord1, tr.coord2);
	vec_sub(ac, tr.coord1, tr.coord3);
	cross_p(info->n, ab, ac);
	normalize(info->n);
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
	set_triangle_normal(elem->tr[index], info);
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
