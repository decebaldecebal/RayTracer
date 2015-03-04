/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:13:56 by rserban           #+#    #+#             */
/*   Updated: 2014/11/10 17:11:20 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n-- && (*(unsigned char *)s1++ == *(unsigned char *)s2++)
			&& s1 != 0 && s2 != 0)
		;
	if (s1 == 0 && s2 == 0)
		return (0);
	return (*(unsigned char *)--s1 - *(unsigned char *)--s2);
}
