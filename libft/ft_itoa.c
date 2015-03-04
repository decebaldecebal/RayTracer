/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 16:05:18 by rserban           #+#    #+#             */
/*   Updated: 2014/11/13 16:32:44 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_nbr_to_str(int len, int n, int sign)
{
	char *str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len--] = '\0';
	if (sign == -1)
		str[0] = '-';
	while (n)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	int temp;
	int sign;
	int l;

	l = 0;
	temp = n;
	sign = 1;
	if (n == -2147483648)
		return ("-2147483648");
	if (n < 0)
	{
		sign = -1;
		n *= -1;
		l++;
	}
	if (n == 0)
		return ("0");
	while (temp)
	{
		l++;
		temp /= 10;
	}
	return (ft_nbr_to_str(l, n, sign));
}
