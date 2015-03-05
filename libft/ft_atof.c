/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoidouble.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuresan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/01 20:04:40 by lmuresan          #+#    #+#             */
/*   Updated: 2015/03/05 15:27:06 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	transform_float(float *a, int dec)
{
	float n;

	n = 1;
	while (dec > 0)
	{
		n *= 10;
		dec--;
	}
	*a /= n;
}

void	if_dot(const char **str, float *a, int *dec)
{
	while (**str >= '0' && **str <= '9')
	{
		*a *= 10;
		*a += (float)(**str - '0');
		(*str)++;
		if (**str == '.')
		{
			(*str)++;
			while (**str >= '0' && **str <= '9')
			{
				*a *= 10;
				*a += (float)(**str - '0');
				(*str)++;
				(*dec)++;
			}
		}
	}
}

float	ft_atof(const char *str)
{
	float	a;
	float	s;
	int		dec;

	dec = 0;
	a = 0;
	s = 1;
	while (str && *str)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
				|| *str == '\f' || *str == '\v')
			str++;
		if (*str == '+' || *str == '-')
		{
			if (*str == '-')
				s = -1;
			str++;
		}
		if_dot(&str, &a, &dec);
		transform_float(&a, dec);
		return (a * s);
	}
	return (0);
}
