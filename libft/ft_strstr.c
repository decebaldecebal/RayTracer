/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:39:34 by rserban           #+#    #+#             */
/*   Updated: 2014/11/11 16:43:45 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char *tp;
	char *tp2;

	if (!*s2)
		return ((char *)s1);
	while (*s1)
	{
		tp = (char *)s1;
		tp2 = (char *)s2;
		while (*s1 && *tp2 && *s1 == *tp2)
		{
			s1++;
			tp2++;
		}
		if (*tp2 == '\0')
			return ((char *)tp);
		s1++;
	}
	return (NULL);
}
