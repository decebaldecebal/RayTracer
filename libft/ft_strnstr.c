/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:57:27 by rserban           #+#    #+#             */
/*   Updated: 2014/11/11 16:43:23 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*tp;
	char	*tp2;
	size_t	m;

	if (!*s2)
		return ((char *)s1);
	while (*s1 && n)
	{
		m = n;
		tp = (char *)s1;
		tp2 = (char *)s2;
		while (*s1 && *tp2 && m && *s1 == *tp2)
		{
			s1++;
			tp2++;
			m--;
		}
		if (*tp2 == '\0')
			return ((char *)tp);
		n--;
		s1++;
	}
	return (NULL);
}
