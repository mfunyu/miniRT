/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:29:27 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/07 15:53:48 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include "cylinder.h"

void	set_info_vecs(t_info *info, double s[3], double center[3], t_cy cy)
{
	double	d[3];
	double	p[3];
	double	n[3];
	int		k;

	set_vec(d, info->dc);
	rotate(cy.n, d, 1);
	k = 0;
	while (k < 3)
	{
		p[k] = s[k] + d[k] * info->t;
		n[k] = 2 * (p[k] - center[k]);
		k++;
	}
	n[Y] = 0;
	rotate(cy.n, n, -1);
	rotate(cy.n, p, -1);
	set_vec(info->n, n);
	set_vec(info->p, p);
}

double	calc_cylinder(double dvec[3], double s[3], double center[3], t_cy cy)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t;

	rotate(cy.n, dvec, 1);
	rotate(cy.n, s, 1);
	rotate(cy.n, center, 1);
	a = pow(dvec[X], 2) + pow(dvec[Z], 2);
	b = (s[X] - center[X]) * dvec[X] + (s[Z] - center[Z]) * dvec[Z];
	c = pow(s[X] - center[X], 2) + pow(s[Z] - center[Z], 2) - pow(cy.r, 2);
	if ((d = (b * b) - (a * c)) < 0)
		return (-1);
	if ((t = (-b - sqrt(d)) / a) < 0)
		t = (-b + sqrt(d)) / a;
	else if (fabs((s[Y] + dvec[Y] * t) - center[Y]) > fabs(cy.height / 2))
		t = (-b + sqrt(d)) / a;
	if (fabs((s[Y] + dvec[Y] * t) - center[Y]) > fabs(cy.height / 2))
		return (-1);
	return (t);
}

void	set_cylinder(t_c camera, t_info *info, t_elem *elem, int index)
{
	double	dcopy[3];
	double	scopy[3];
	double	ccopy[3];
	double	t;

	set_vec(dcopy, info->dc);
	set_vec(scopy, camera.coord);
	set_vec(ccopy, elem->cy[index].center);
	t = calc_cylinder(dcopy, scopy, ccopy, elem->cy[index]);
	if (t < 0 || !(info->index == -1 || info->t > t))
		return ;
	info->type = CYLINDER;
	info->index = index;
	info->t = t;
	set_vec(info->rgb, elem->cy[index].rgb);
	set_pvec(info->p, camera.coord, info->dc, t);
	set_info_vecs(info, scopy, ccopy, elem->cy[index]);
	adjust_normal_vec(info->n, camera.coord, info->p);
}

int		is_behind_cy(t_info *info, t_elem *elem, int index)
{
	double	dcopy[3];
	double	pcopy[3];
	double	ccopy[3];
	double	t;
	int		i;

	i = 0;
	while (elem->cy[i].exist)
	{
		if (info->type == CYLINDER && info->index == i)
		{
			i++;
			continue;
		}
		vec_sub(dcopy, info->p, elem->l[index].coord);
		set_vec(pcopy, info->p);
		set_vec(ccopy, elem->cy[i].center);
		t = calc_cylinder(dcopy, pcopy, ccopy, elem->cy[i]);
		if (t > 0 && is_closer(dcopy, t))
			break ;
		i++;
	}
	if (elem->cy[i].exist)
		return (1);
	return (0);
}
