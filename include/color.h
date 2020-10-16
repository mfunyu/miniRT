/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:23:32 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/18 21:18:27 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "minirt.h"

double	*apply_ambient(t_a ambient);

int		calc_rgb(double *color_vec);
void	calc_cos(t_l light, t_info *info, double *cosa, double *cosr);

#endif
