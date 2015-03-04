/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:42:28 by rserban           #+#    #+#             */
/*   Updated: 2014/11/10 17:27:30 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *dst;
	char *ret;

	dst = (char *)malloc(ft_strlen((char *)s1) + 1);
	ret = dst;
	if (dst)
	{
		while ((*dst++ = *s1++) != '\0')
			;
	}
	return (ret);
}
