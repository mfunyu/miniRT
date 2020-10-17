/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:02:34 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/17 12:58:37 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include "read.h"
#include "exit.h"
#include "color.h"

int		closest_obj(t_info *info, t_elem *elem, t_screen *sc)
{
	int		i;

	i = 0;
	info->index = -1;
	while (elem->pl[i].exist)
		set_plane(sc->camera, info, elem, i++);
	i = 0;
	while (elem->sp[i].exist)
		set_sphere(sc->camera, info, elem, i++);
	i = 0;
	while (elem->sq[i].exist)
		set_square(sc->camera, info, elem, i++);
	i = 0;
	while (elem->cy[i].exist)
		set_cylinder(sc->camera, info, elem, i++);
	i = 0;
	while (elem->tr[i].exist)
		set_triangle(sc->camera, info, elem, i++);
	return (info->index);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + x * (img->bpp / 8) + (y * img->line_len);
	*(unsigned int *)dst = color;
}

/*
** bpp: 32
** 255 255 0 0 255 255 0 0 0 0 0 0 0 0
** 255 255 0 0 255 255 0 0 0 0 0 0 0 0
*/

void	create_img(t_img *img, t_elem *elem, int camera)
{
	t_info		*info;
	t_screen	screen;
	int			y;
	int			x;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		exit_failure(errno);
	if (elem->c[camera].exist)
		set_screen(&screen, elem, elem->c[camera]);
	y = -1;
	while (++y < elem->r.height)
	{
		x = -1;
		while (++x < elem->r.width)
		{
			if (!elem->c[camera].exist)
			{
				my_mlx_pixel_put(img, x, y, 0);
				continue ;
			}
			set_screen_vec(&screen, info, x, y);
			if (closest_obj(info, elem, &screen) >= 0)
				my_mlx_pixel_put(img, x, y, set_color(info, elem));
			else
				my_mlx_pixel_put(img, x, y, 0);
		}
	}
	SAFE_FREE(info);
}
