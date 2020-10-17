/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:23:32 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/17 13:08:38 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "minirt.h"

double	dot_p(double *p1, double *p2);
void	cross_p(double dest[3], double a[3], double b[3]);
void	vec_add(double dst[3], double *v1, double *v2);
void	vec_sub(double dst[3], double *v1, double *v2);
void	vec_multi(double dst[3], double val);

void	normalize(double vec[3]);
void	set_vec(double dst[3], double src[3]);
void	set_pvec(double pvec[3], double position[3],
					double direction[3], double length);
double	is_closer(double d[3], double t);
void	adjust_normal_vec(double n[3], double origin[3], double dest[3]);

#endif
