/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:38:03 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/16 20:31:37 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "exit.h"

void	exit_failure(int n)
{
	ft_putstr_fd("Error\n: ", 1);
	if (n == -1)
		ft_putendl_fd("Invalid file type", 1);
	else if (n == -2)
		ft_putendl_fd("Invalid file format", 1);
	else
		ft_putendl_fd(strerror(n), 1);
	exit(EXIT_FAILURE);
}

void	free_elem(t_elem *elem)
{
	SAFE_FREE(elem->c);
	SAFE_FREE(elem->l);
	SAFE_FREE(elem->pl);
	SAFE_FREE(elem->sp);
	SAFE_FREE(elem->sq);
	SAFE_FREE(elem->cy);
	SAFE_FREE(elem->tr);
	SAFE_FREE(elem);
}

int		close_exit(t_mlx *mlx)
{
	int		i;

	i = 0;
	while (mlx->imgdata[i].image)
	{
		mlx_destroy_image(mlx->mlx, mlx->imgdata[i].image);
		i++;
	}
	SAFE_FREE(mlx->imgdata);
	SAFE_FREE(mlx->mlx);
	free_elem(mlx->elem);
	exit(EXIT_SUCCESS);
}

int		reput_img(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->window,
								mlx->imgdata[mlx->c_index].image, 0, 0);
	return (0);
}

int		key_hook(int key, void *param)
{
	t_mlx	*mlx;
	int		c_num;

	mlx = (t_mlx *)param;
	if (key == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		close_exit(mlx);
	}
	if (key == CHANGE)
	{
		c_num = 0;
		while (mlx->imgdata[c_num].image)
			c_num++;
		mlx->c_index = (mlx->c_index + 1) % c_num;
		mlx_clear_window(mlx->mlx, mlx->window);
		mlx_put_image_to_window(mlx->mlx, mlx->window,
								mlx->imgdata[mlx->c_index].image, 0, 0);
	}
	return (0);
}
