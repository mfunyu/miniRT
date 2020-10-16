/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:23:32 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/16 20:37:27 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <string.h>

# include "minirt.h"

# define FOCUS_IN 9
# define DESTROY_NOTIFY 17

# define FOCUS_CHANGE_MASK 1L << 21
# define STRUCTURE_NOTIFY_MASK 1L << 17

void	exit_failure(int n);
int		close_exit(t_mlx *mlx);
int		reput_img(t_mlx *mlx);
int		key_hook(int key, void *param);

#endif
