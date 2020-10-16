/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:52:21 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/22 20:24:12 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "output.h"
#include "objects.h"
#include "color.h"
#include "exit.h"

int		is_behind(t_info *info, t_elem *elem, int index)
{
	double	direction[3];
	int		k;

	vec_sub(direction, info->p, elem->l[index].coord);
	k = 0;
	while (k < 3)
	{
		info->p[k] += EPSILON * direction[k];
		k++;
	}
	if (is_behind_pl(info, elem, index))
		return (1);
	if (is_behind_sp(info, elem, index))
		return (1);
	if (is_behind_sq(info, elem, index))
		return (1);
	if (is_behind_cy(info, elem, index))
		return (1);
	if (is_behind_tr(info, elem, index))
		return (1);
	return (0);
}

double	*apply_ambient(t_a ambient)
{
	double	*color;
	int		k;

	if (!(color = (double *)malloc(sizeof(double) * 4)))
		exit_failure(errno);
	k = 0;
	while (k < 3)
	{
		color[k] = ambient.rgb[k] * ambient.ratio;
		k++;
	}
	return (color);
}

double	diffuse_r(t_info obj, t_l light, double cosa, int index)
{
	return (obj.rgb[index] * cosa * light.ratio);
}

double	specular_r(t_l light, double cosr, int index)
{
	return (light.rgb[index] * cosr * light.ratio);
}

int		set_color(t_info *info, t_elem *elem)
{
	double	*color;
	double	cosa;
	double	cosr;
	int		light_i;
	int		k;

	color = apply_ambient(elem->a);
	normalize(info->dc);
	light_i = -1;
	while (elem->l[++light_i].exist)
	{
		if (!is_behind(info, elem, light_i))
		{
			calc_cos(elem->l[light_i], info, &cosa, &cosr);
			k = 0;
			while (k < 3)
			{
				color[k] += diffuse_r(*info, elem->l[light_i], cosa, k);
				color[k] += specular_r(elem->l[light_i], cosr, k);
				color[k] = MIN(color[k], 255);
				k++;
			}
		}
	}
	return (calc_rgb(color));
}
