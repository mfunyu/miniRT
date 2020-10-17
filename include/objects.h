/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 12:54:29 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/17 12:13:54 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef enum	e_object_type
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
	TRIANGLE,
}				t_object_type;

typedef struct	s_r
{
	int			width;
	int			height;
}				t_r;

typedef struct	s_a
{
	double		ratio;
	double		rgb[3];
}				t_a;

typedef struct	s_c
{
	int			exist;
	double		coord[3];
	double		n[3];
	double		fov;
}				t_c;

typedef struct	s_l
{
	int			exist;
	double		coord[3];
	double		ratio;
	double		rgb[3];
}				t_l;

typedef struct	s_pl
{
	int			exist;
	double		coord[3];
	double		n[3];
	double		rgb[3];
}				t_pl;

typedef struct	s_sp
{
	int			exist;
	double		center[3];
	double		r;
	double		rgb[3];
}				t_sp;

typedef struct	s_sq
{
	int			exist;
	double		center[3];
	double		n[3];
	double		size;
	double		rgb[3];
}				t_sq;

typedef struct	s_cy
{
	int			exist;
	double		center[3];
	double		n[3];
	double		r;
	double		height;
	double		rgb[3];
}				t_cy;

typedef struct	s_tr
{
	int			exist;
	double		coord1[3];
	double		coord2[3];
	double		coord3[3];
	double		rgb[3];
}				t_tr;

typedef struct	s_elem
{
	t_r			r;
	t_a			a;
	t_c			*c;
	t_l			*l;
	t_sp		*sp;
	t_pl		*pl;
	t_sq		*sq;
	t_cy		*cy;
	t_tr		*tr;
}				t_elem;

#endif
