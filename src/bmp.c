/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 14:43:42 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/01 19:39:51 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "read.h"
#include "exit.h"

void	insert_header(char *data, int width, int height)
{
	int		size;

	size = width * height * 3 + 54;
	*(unsigned int *)data = (unsigned int)'B';
	*(unsigned int *)(data + 1) = (unsigned int)'M';
	*(unsigned int *)(data + 2) = (unsigned long)size;
	*(unsigned int *)(data + 6) = (unsigned int)0;
	*(unsigned int *)(data + 8) = (unsigned int)0;
	*(unsigned int *)(data + 10) = (unsigned int)54;
	*(unsigned int *)(data + 14) = (unsigned long)40;
	*(unsigned int *)(data + 18) = (long)width;
	*(unsigned int *)(data + 22) = (long)-height;
	*(unsigned int *)(data + 26) = (unsigned int)1;
	*(unsigned int *)(data + 28) = (unsigned int)24;
	*(unsigned int *)(data + 30) = (unsigned long)0;
	*(unsigned int *)(data + 34) = (unsigned long)(size - 54);
	*(unsigned int *)(data + 38) = (long)0;
	*(unsigned int *)(data + 42) = (long)0;
	*(unsigned int *)(data + 46) = (unsigned long)0;
	*(unsigned int *)(data + 50) = (unsigned long)0;
}

/*
** bpp: 32
** 255 255 0 0 255 255 0 0 0 0 0 0 0 0
** 255 255 0 0 255 255 0 0 0 0 0 0 0 0
*/

void	insert_img_data(t_img img, char *data, int width, int height)
{
	char	*color;
	int		now;
	int		x;
	int		y;
	int		padding;

	now = 54;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			color = img.addr + x * (img.bpp / 8) + (y * img.line_len);
			*(unsigned char *)(data + now++) = *(unsigned char *)color++;
			*(unsigned char *)(data + now++) = *(unsigned char *)color++;
			*(unsigned char *)(data + now++) = *(unsigned char *)color++;
			x++;
		}
		padding = width % 4;
		while (padding--)
			*(data + now++) = 0;
		y++;
	}
}

void	write_img_data(t_img img, int fd, int width, int height)
{
	char	*data;
	int		total_bytes;

	total_bytes = (width + (width * 3) % 4) * height * 3 + 54;
	if (!(data = malloc(total_bytes + 1)))
		exit_failure(errno);
	insert_header(data, width, height);
	insert_img_data(img, data, width, height);
	write(fd, data, total_bytes);
	SAFE_FREE(data);
}

void	create_name(char **name, int i)
{
	char	*name_head;
	char	*number;

	number = ft_itoa(i + 1);
	name_head = ft_strjoin("camera_", number);
	*name = ft_strjoin(name_head, ".bmp");
	SAFE_FREE(number);
	SAFE_FREE(name_head);
}

int		create_bmp(t_img *img, int width, int height)
{
	char	*name;
	int		fd;
	int		i;

	i = 0;
	while (img[i].image)
	{
		create_name(&name, i);
		fd = open(name, O_CREAT | O_RDWR, 0644);
		write_img_data(img[i], fd, width, height);
		SAFE_FREE(name);
		close(fd);
		i++;
	}
	return (0);
}
