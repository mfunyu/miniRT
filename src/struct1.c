/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:48:39 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/17 12:28:03 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "exit.h"
#include "calc.h"

void	init_struct(t_elem *elem, int *cnt)
{
	if (cnt[0] != 1 || cnt[1] > 1)
		exit_failure(-2);
	if (!cnt[1])
	{
		double vec[3] = {0,0,0};
		elem->a.ratio = 0;
		set_vec(elem->a.rgb, vec);
	}
	if (!(elem->c = (t_c *)ft_calloc(cnt[2] + 1, sizeof(t_c))))
		exit_failure(errno);
	if (!(elem->l = (t_l *)ft_calloc(cnt[3] + 1, sizeof(t_l))))
		exit_failure(errno);
	if (!(elem->sp = (t_sp *)ft_calloc(cnt[4] + 1, sizeof(t_sp))))
		exit_failure(errno);
	if (!(elem->pl = (t_pl *)ft_calloc(cnt[5] + 1, sizeof(t_pl))))
		exit_failure(errno);
	if (!(elem->sq = (t_sq *)ft_calloc(cnt[6] + 1, sizeof(t_sq))))
		exit_failure(errno);
	if (!(elem->cy = (t_cy *)ft_calloc(cnt[7] + 1, sizeof(t_cy))))
		exit_failure(errno);
	if (!(elem->tr = (t_tr *)ft_calloc(cnt[8] + 1, sizeof(t_tr))))
		exit_failure(errno);
}

void	init_r(char *line, t_elem *elem)
{
	int		error;

	error = 0;
	skip_spaces(&line);
	if ((elem->r.width = ft_atod(&line, &error)) <= 0)
		exit_failure(-2);
	skip_spaces(&line);
	if ((elem->r.height = ft_atod(&line, &error)) <= 0)
		exit_failure(-2);
	skip_spaces(&line);
	if (error || *line)
		exit_failure(-2);
}

void	init_a(char *line, t_elem *elem)
{
	int		error;

	error = 0;
	elem->a.ratio = ft_atod(&line, &error);
	range_error(0.0, 1.0, elem->a.ratio, &error);
	init_vector(elem->a.rgb, &line, &error, RGB);
	skip_spaces(&line);
	if (error || *line)
		exit_failure(-2);
}

void	init_c(char *line, t_elem *elem)
{
	int		error;
	int		i;

	error = 0;
	i = 0;
	while (elem->c[i].exist)
		i++;
	elem->c[i].exist = 1;
	init_vector(elem->c[i].coord, &line, &error, COORD);
	init_vector(elem->c[i].n, &line, &error, NORMAL);
	elem->c[i].fov = ft_atod(&line, &error);
	range_error(0.0, 180.0, elem->c[i].fov, &error);
	skip_spaces(&line);
	if (error || *line)
		exit_failure(-2);
}

void	init_l(char *line, t_elem *elem)
{
	int		error;
	int		i;

	error = 0;
	i = 0;
	while (elem->l[i].exist)
		i++;
	elem->l[i].exist = 1;
	init_vector(elem->l[i].coord, &line, &error, COORD);
	elem->l[i].ratio = ft_atod(&line, &error);
	range_error(0.0, 1.0, elem->l[i].ratio, &error);
	init_vector(elem->l[i].rgb, &line, &error, RGB);
	skip_spaces(&line);
	if (error || *line)
		exit_failure(-2);
}
