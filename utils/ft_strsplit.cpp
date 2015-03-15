/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/10 16:14:01 by rserban           #+#    #+#             */
/*   Updated: 2014/11/15 14:05:57 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

static int	ft_word_size(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	ft_put_words(char **str, char *s, char c, int nr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < nr)
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') ||
				(i == 0 && s[0] != c))
		{
			if (s[i] == c)
				i++;
			str[j] = ft_strsub(s, i, ft_word_size(&s[i], c));
			j++;
		}
		i++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		nr;

	if (s == NULL)
		return (NULL);
	i = 0;
	nr = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') ||
			(i == 0 && s[0] != c))
			nr++;
		i++;
	}
	str = (char **)malloc(sizeof(char *) * (nr + 1));
	if (str)
	{
		ft_put_words(str, (char *)s, c, nr);
		str[nr] = '\0';
		return (str);
	}
	return (NULL);
}
