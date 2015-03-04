/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 18:07:30 by rserban           #+#    #+#             */
/*   Updated: 2014/11/13 16:05:08 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_can_trim(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (ft_can_trim(s[i]))
		i++;
	str = ft_strsub(s, i, ft_strlen(s) - i);
	if (str)
	{
		i = 0;
		j = 0;
		while (str[i])
		{
			if (ft_can_trim(str[i]))
				j++;
			if (!ft_can_trim(str[i]))
				j = 0;
			i++;
		}
		str[ft_strlen(str) - j] = '\0';
		return (str);
	}
	return (NULL);
}
