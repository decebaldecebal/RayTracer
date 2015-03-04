/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 17:21:25 by rserban           #+#    #+#             */
/*   Updated: 2014/11/11 17:52:31 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*inf;

	inf = (void *)malloc(size * sizeof(void));
	if (inf && size > 0)
	{
		ft_bzero(inf, size);
		return (inf);
	}
	return (NULL);
}
