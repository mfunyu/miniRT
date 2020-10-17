/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:25:03 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/17 16:07:44 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "mlx.h"
# include "minirt.h"
# include "calc.h"

# define EPSILON 1e-6f

typedef struct	s_screen
{
	double	top[3];
	double	x[3];
	double	y[3];
	double	unit;
	t_c		camera;
}				t_screen;

/*
** screen
*/
void			set_screen(t_screen *sc, t_elem *elem, t_c camera);
void			set_screen_vec(t_screen *sc, t_info *info, double x, double y);

/*
** color
*/
int				set_color(t_info *info, t_elem *elem);

/*
** objects
*/
int				is_behind_pl(t_info *info, t_elem *elem, int index);
int				is_behind_sp(t_info *info, t_elem *elem,
								int index, double adjusted[3]);
int				is_behind_sq(t_info *info, t_elem *elem, int index);
int				is_behind_cy(t_info *info, t_elem *elem,
								int index, double adjusted[3]);
int				is_behind_tr(t_info *info, t_elem *elem, int index);

void			set_plane(t_c camera, t_info *info, t_elem *elem, int index);
void			set_sphere(t_c camera, t_info *info, t_elem *elem, int index);
void			set_square(t_c camera, t_info *info, t_elem *elem, int index);
void			set_cylinder(t_c camera, t_info *info, t_elem *elem, int index);
void			set_triangle(t_c camera, t_info *info, t_elem *elem, int index);

double			calc_plane(double origin[3], double coord[3],
								double n[3], double d[3]);
double			calc_triangle(double d[3], double s[3], t_tr tr);

#endif
