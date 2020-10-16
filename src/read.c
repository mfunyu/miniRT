/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 12:51:22 by mfunyu            #+#    #+#             */
/*   Updated: 2020/10/01 20:40:32 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minirt.h"
#include "read.h"
#include "exit.h"

void	parse_identifier(char *line, t_elem *elem)
{
	if (!*line)
		return ;
	skip_spaces(&line);
	if (!ft_strncmp(line, "R", 1) && is_space(line[1]))
		init_r(line + 1, elem);
	else if (!ft_strncmp(line, "A", 1) && is_space(line[1]))
		init_a(line + 1, elem);
	else if (!ft_strncmp(line, "c", 1) && is_space(line[1]))
		init_c(line + 1, elem);
	else if (!ft_strncmp(line, "l", 1) && is_space(line[1]))
		init_l(line + 1, elem);
	else if (!ft_strncmp(line, "pl", 2) && is_space(line[2]))
		init_pl(line + 2, elem);
	else if (!ft_strncmp(line, "sp", 2) && is_space(line[2]))
		init_sp(line + 2, elem);
	else if (!ft_strncmp(line, "sq", 2) && is_space(line[2]))
		init_sq(line + 2, elem);
	else if (!ft_strncmp(line, "cy", 2) && is_space(line[2]))
		init_cy(line + 2, elem);
	else if (!ft_strncmp(line, "tr", 2) && is_space(line[2]))
		init_tr(line + 2, elem);
	else if (*line == '#')
		return ;
	else
		exit_failure(-2);
}

void	cnt_elems(char *line, int *cnt)
{
	skip_spaces(&line);
	if (!ft_strncmp(line, "R", 1) && is_space(line[1]))
		cnt[0]++;
	else if (!ft_strncmp(line, "A", 1) && is_space(line[1]))
		cnt[1]++;
	else if (!ft_strncmp(line, "c", 1) && is_space(line[1]))
		cnt[2]++;
	else if (!ft_strncmp(line, "l", 1) && is_space(line[1]))
		cnt[3]++;
	else if (!ft_strncmp(line, "sp", 2) && is_space(line[2]))
		cnt[4]++;
	else if (!ft_strncmp(line, "pl", 2) && is_space(line[2]))
		cnt[5]++;
	else if (!ft_strncmp(line, "sq", 2) && is_space(line[2]))
		cnt[6]++;
	else if (!ft_strncmp(line, "cy", 2) && is_space(line[2]))
		cnt[7]++;
	else if (!ft_strncmp(line, "tr", 2) && is_space(line[2]))
		cnt[8]++;
}

void	read_cnt_elems(char *filename, int **cnt)
{
	char	*line;
	int		fd;
	int		ret;

	line = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		exit_failure(errno);
	if ((ft_strncmp(filename + ft_strlen(filename) - 3, ".rt", 3)))
	{
		close(fd);
		exit_failure(-1);
	}
	if (!(*cnt = (int *)ft_calloc(10, sizeof(int))))
		exit_failure(errno);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (*line)
			cnt_elems(line, *cnt);
		SAFE_FREE(line);
	}
	SAFE_FREE(line);
	close(fd);
	if (ret < 0)
		exit_failure(errno);
}

void	read_file(char *filename, t_elem *elem)
{
	int		fd;
	int		ret;
	int		*cnt;
	char	*line;

	cnt = NULL;
	read_cnt_elems(filename, &cnt);
	init_struct(elem, cnt);
	line = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		exit_failure(errno);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (*line)
			parse_identifier(line, elem);
		SAFE_FREE(line);
	}
	SAFE_FREE(line);
	SAFE_FREE(cnt);
	close(fd);
	if (ret < 0)
		exit_failure(errno);
}
