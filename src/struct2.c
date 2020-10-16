/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:48:39 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/01 20:40:22 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "exit.h"

void	init_pl(char *line, t_elem *elem)
{
	int		error;
	int		i;

	error = 0;
	i = 0;
	while (elem->pl[i].exist)
		i++;
	elem->pl[i].exist = 1;
	init_vector(elem->pl[i].coord, &line, &error, COORD);
	init_vector(elem->pl[i].n, &line, &error, NORMAL);
	init_vector(elem->pl[i].rgb, &line, &error, RGB);
	skip_spaces(&line);
	if (error || *line)
		exit_failure(-2);
}

void	init_sp(char *line, t_elem *elem)
{
	int		error;
	int		i;

	error = 0;
	i = 0;
	while (elem->sp[i].exist)
		i++;
	elem->sp[i].exist = 1;
	init_vector(elem->sp[i].center, &line, &error, COORD);
	elem->sp[i].r = ft_atod(&line, &error) / 2;
	init_vector(elem->sp[i].rgb, &line, &error, RGB);
	skip_spaces(&line);
	if (error || *line)
		exit_failure(-2);
}

void	init_sq(char *line, t_elem *elem)
{
	int		error;
	int		i;

	error = 0;
	i = 0;
	while (elem->sq[i].exist)
		i++;
	elem->sq[i].exist = 1;
	init_vector(elem->sq[i].center, &line, &error, COORD);
	init_vector(elem->sq[i].n, &line, &error, NORMAL);
	elem->sq[i].size = ft_atod(&line, &error);
	init_vector(elem->sq[i].rgb, &line, &error, RGB);
	skip_spaces(&line);
	if (error || *line)
		exit_failure(-2);
}

void	init_cy(char *line, t_elem *elem)
{
	int		error;
	int		i;

	error = 0;
	i = 0;
	while (elem->cy[i].exist)
		i++;
	elem->cy[i].exist = 1;
	init_vector(elem->cy[i].center, &line, &error, COORD);
	init_vector(elem->cy[i].n, &line, &error, NORMAL);
	elem->cy[i].r = ft_atod(&line, &error) / 2;
	elem->cy[i].height = ft_atod(&line, &error);
	init_vector(elem->cy[i].rgb, &line, &error, RGB);
	skip_spaces(&line);
	if (error || *line)
		exit_failure(-2);
}

void	init_tr(char *line, t_elem *elem)
{
	int		error;
	int		i;

	error = 0;
	i = 0;
	while (elem->tr[i].exist)
		i++;
	elem->tr[i].exist = 1;
	init_vector(elem->tr[i].coord1, &line, &error, COORD);
	init_vector(elem->tr[i].coord2, &line, &error, COORD);
	init_vector(elem->tr[i].coord3, &line, &error, COORD);
	init_vector(elem->tr[i].rgb, &line, &error, RGB);
	skip_spaces(&line);
	if (error || *line)
		exit_failure(-2);
}
