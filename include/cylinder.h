/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 14:26:05 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/01 19:45:30 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include <math.h>

# include "minirt.h"

void	rotate(double centerline[3], double set[3], int sign);
double	dot_p_2d(double v1[3], double v2[3], int index1, int index2);
double	len_2d_vec(double vec[3], double index1, double index2);

#endif
