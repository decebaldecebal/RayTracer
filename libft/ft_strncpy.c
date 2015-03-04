/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 17:42:33 by rserban           #+#    #+#             */
/*   Updated: 2014/11/15 14:55:29 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char *rez;

	rez = dst;
	while (n--)
		if ((*dst++ = *src++) == '\0')
		{
			while (n--)
				*dst++ = '\0';
			return (rez);
		}
	return (rez);
}
