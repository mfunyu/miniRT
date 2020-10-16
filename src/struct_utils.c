/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 12:11:09 by mfunyu            #+#    #+#             */
/*   Updated: 2020/09/23 11:24:31 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

int			is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
	|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

void		skip_spaces(char **str)
{
	while (is_space(**str))
		(*str)++;
}

void		range_error(double min, double max, double eval, int *error)
{
	if (!(min <= eval && eval <= max))
		*error = 1;
}

void		init_vector(double ptr[3], char **str,
							int *error, t_vectype type)
{
	int		k;

	if (*error)
		return ;
	skip_spaces(str);
	k = 0;
	while (k < 3)
	{
		ptr[k] = ft_atod(str, error);
		if (type == NORMAL)
			range_error(-1.0, 1.0, ptr[k], error);
		if (type == RGB)
			range_error(0.0, 255.0, ptr[k], error);
		if (*error || (k < 2 && **str != ','))
		{
			*error = 1;
			break ;
		}
		if (k < 2)
			(*str)++;
		k++;
	}
	if (type == NORMAL)
		if (!ptr[X] && !ptr[Y] && !ptr[Z])
			*error = 1;
}

double		ft_atod(char **s, int *error)
{
	double	nb;
	int		sign;
	int		digits;

	nb = 0;
	digits = -1;
	skip_spaces(s);
	sign = (**s == '-' ? -1 : 1);
	if (**s == '-' || **s == '+')
		(*s)++;
	if (!ft_isdigit(**s))
		*error = 1;
	while (ft_isdigit(**s) || (**s == '.' && digits == -1))
	{
		if (**s == '.' || digits >= 0)
			digits++;
		if (digits != 0)
			nb = nb * 10 + (**s - '0');
		(*s)++;
	}
	if (**s == '.' && digits != -1)
		*error = 1;
	while (digits-- > 0)
		nb /= 10;
	return (nb * sign);
}
