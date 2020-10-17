/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 12:44:59 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/17 13:09:16 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "exit.h"

void	set_screen_size(t_mlx *mlx, t_elem *elem)
{
	int		sizex;
	int		sizey;

	mlx_get_screen_size(mlx->mlx, &sizex, &sizey);
	elem->r.width = MIN(elem->r.width, sizex);
	elem->r.height = MIN(elem->r.height, sizey);
}

void	init_t_mlx(t_mlx *mlx, t_elem *elem)
{
	t_img	*img;
	int		c_num;
	int		i;

	mlx->mlx = mlx_init();
	set_screen_size(mlx, elem);
	mlx->elem = elem;
	mlx->c_index = 0;
	c_num = 0;
	while (elem->c[c_num].exist)
		c_num++;
	if (!c_num)
		c_num++;
	mlx->imgdata = ft_calloc((c_num + 1), sizeof(t_img));
	i = 0;
	while (i < c_num)
	{
		img = &mlx->imgdata[i];
		img->image = mlx_new_image(mlx->mlx, elem->r.width, elem->r.height);
		img->addr = mlx_get_data_addr(img->image, &img->bpp, &img->line_len,
										&img->endian);
		i++;
	}
}

void	start_mlx_loop(t_mlx *mlx, t_elem *elem, char *name)
{
	mlx->window = mlx_new_window(mlx->mlx, elem->r.width, elem->r.height, name);
	if (!mlx->window)
		exit_failure(errno);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->imgdata[0].image, 0, 0);
	mlx_key_hook(mlx->window, &key_hook, (void *)mlx);
	mlx_hook(mlx->window, FOCUS_IN, FOCUS_CHANGE_MASK, &reput_img, (void *)mlx);
	mlx_hook(mlx->window, DESTROY_NOTIFY,
				STRUCTURE_NOTIFY_MASK, &close_exit, (void *)mlx);
	mlx_loop(mlx->mlx);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	t_elem	*elem;
	int		i;

	if (ac != 2 && !(ac == 3 && !ft_strncmp(av[2], "--save", 7)))
		exit_failure(22);
	if (!(elem = (t_elem *)malloc(sizeof(t_elem))))
		exit_failure(errno);
	read_file(av[1], elem);
	init_t_mlx(&mlx, elem);
	i = 0;
	while (mlx.imgdata[i].image)
	{
		create_img(&mlx.imgdata[i], elem, i);
		i++;
	}
	if (ac == 3)
		create_bmp(mlx.imgdata, elem->r.width, elem->r.height);
	else
		start_mlx_loop(&mlx, elem, av[1]);
	close_exit(&mlx);
}
