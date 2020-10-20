/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:51:52 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/20 12:37:20 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include "minirt.h"

double	calc_sphere(double dvec[3], double s[3], double center[3], double r)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t;

	a = dot_p(dvec, dvec);
	b = dot_p(s, dvec) - dot_p(dvec, center);
	c = dot_p(s, s) - 2 * dot_p(s, center) + dot_p(center, center) - r * r;
	d = (b * b) - (a * c);
	if (d > 0)
	{
		t = (-b - sqrt(d)) / a;
		if (t < 0)
			t = (-b + sqrt(d)) / a;
		return (t);
	}
	return (-1);
}

void	set_sphere(t_c camera, t_info *info, t_elem *elem, int index)
{
	double	t;

	t = calc_sphere(info->dc, camera.coord,\
		elem->sp[index].center, elem->sp[index].r);
	if (t < 0 || !(info->index == -1 || info->t > t))
		return ;
	info->type = SPHERE;
	info->index = index;
	info->t = t;
	set_vec(info->rgb, elem->sp[index].rgb);
	set_pvec(info->p, camera.coord, info->dc, t);
	vec_sub(info->n, elem->sp[info->index].center, info->p);
	adjust_normal_vec(info->n, camera.coord, info->p);
}

int		is_behind_sp(t_elem *elem, double intersect[3], double direction[3])
{
	double	t;
	int		i;

	i = 0;
	while (elem->sp[i].exist)
	{
		t = calc_sphere(direction, intersect,
							elem->sp[i].center, elem->sp[i].r);
		if (t > 0 && is_closer(direction, t))
			break ;
		i++;
	}
	if (elem->sp[i].exist)
		return (1);
	return (0);
}
