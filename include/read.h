/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:23:32 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/18 20:41:16 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include <fcntl.h>
# include <string.h>

# include "minirt.h"

typedef enum	e_vectype
{
	NORMAL,
	RGB,
	COORD
}				t_vectype;

/*
** init_struct_utils
*/
int		is_space(char c);
void	skip_spaces(char **str);
void	init_vector(double ptr[3], char **str, int *error, t_vectype type);
double	ft_atod(char **s, int *error);
void	range_error(double min, double max, double eval, int *error);

/*
** init_struct1
*/
void	init_struct(t_elem *elem, int *cnt);
void	init_r(char *line, t_elem *elem);
void	init_a(char *line, t_elem *elem);
void	init_c(char *line, t_elem *elem);
void	init_l(char *line, t_elem *elem);

/*
** init_struct2
*/
void	init_pl(char *line, t_elem *elem);
void	init_sp(char *line, t_elem *elem);
void	init_sq(char *line, t_elem *elem);
void	init_cy(char *line, t_elem *elem);
void	init_tr(char *line, t_elem *elem);

#endif
