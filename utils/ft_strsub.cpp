/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 17:59:25 by rserban           #+#    #+#             */
/*   Updated: 2014/11/11 18:25:56 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	str = (char *)malloc((len + 1) * sizeof(char));
	if (str)
	{
		i = 0;
		while (len--)
			str[i++] = s[start++];
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
