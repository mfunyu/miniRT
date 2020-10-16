/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:52:21 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/23 11:21:11 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "output.h"

int		calc_rgb(double *color_vec)
{
	long long color;

	color = (int)color_vec[0] << 16;
	color += (int)color_vec[1] << 8;
	color += (int)color_vec[2];
	SAFE_FREE(color_vec);
	return (color);
}

void	calc_cos(t_l light, t_info *info, double *cosa, double *cosr)
{
	double	to_light[3];
	double	reflection[3];
	int		k;

	vec_sub(to_light, info->p, light.coord);
	normalize(to_light);
	*cosa = dot_p(to_light, info->n);
	*cosa = MAX(0, *cosa);
	*cosa = MIN(*cosa, 1);
	if (!*cosa)
	{
		*cosr = 0;
		return ;
	}
	k = 0;
	while (k < 3)
	{
		reflection[k] = 2 * (*cosa) * info->n[k] - to_light[k];
		k++;
	}
	normalize(reflection);
	*cosr = -dot_p(reflection, info->dc);
	*cosr = MAX(0, *cosr);
	*cosr = pow(*cosr, N);
}
