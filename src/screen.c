/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:45:00 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/22 20:34:42 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include "minirt.h"

void	set_screen_vec(t_screen *sc, t_info *info, double x, double y)
{
	double	screen_point[3];
	double	px;
	double	py;
	int		k;

	px = sc->unit * x;
	py = sc->unit * y;
	k = 0;
	while (k < 3)
	{
		screen_point[k] = sc->top[k] + px * sc->x[k] - py * sc->y[k];
		info->dc[k] = screen_point[k] - sc->camera.coord[k];
		k++;
	}
}

void	calc_screen_vec(t_screen *sc, t_c camera)
{
	double	base[3];

	base[X] = 0;
	base[Y] = 0;
	base[Z] = 0;
	if (camera.n[Z] || camera.n[X])
		base[Y] = 1;
	else
		base[Z] = 1;
	cross_p(sc->x, base, camera.n);
	cross_p(sc->y, camera.n, sc->x);
	normalize(sc->x);
	normalize(sc->y);
}

void	set_screen(t_screen *sc, t_elem *elem, t_c camera)
{
	double	center[3];
	double	width;
	double	height;
	int		k;

	calc_screen_vec(sc, camera);
	normalize(camera.n);
	set_pvec(center, camera.coord, camera.n, 1);
	width = tan((camera.fov / 2) / 180 * M_PI) * 2;
	sc->unit = width / elem->r.width;
	height = sc->unit * elem->r.height;
	k = 0;
	while (k < 3)
	{
		sc->top[k] = center[k] - (width / 2 * sc->x[k]) + height / 2 * sc->y[k];
		k++;
	}
	sc->camera = camera;
}
