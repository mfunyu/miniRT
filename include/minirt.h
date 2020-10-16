/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 12:51:48 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/23 11:29:29 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "objects.h"

# include <stdlib.h>
# include <math.h>
# include <errno.h>

# define N 20

# if __APPLE__
#  define ESC 53
#  define CHANGE 8
# else
#  define ESC 0xff1b
#  define CHANGE 0x0063
# endif

# define X 0
# define Y 1
# define Z 2

# define SAFE_FREE(p) free(p); p = NULL;
# define MAX(a, b) ((a > b) ? a : b)
# define MIN(a, b) ((a < b) ? a : b)

typedef struct	s_info
{
	t_object_type	type;
	int				index;
	double			t;
	double			n[3];
	double			p[3];
	double			rgb[3];
	double			dc[3];
}				t_info;

typedef struct	s_img
{
	void		*image;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx;
	void		*window;
	t_elem		*elem;
	t_img		*imgdata;
	int			c_index;
}				t_mlx;

void			read_file(char *filename, t_elem *elem);
void			create_img(t_img *img, t_elem *elem, int camera);
int				create_bmp(t_img *img, int width, int height);

#endif
