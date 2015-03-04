/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 14:40:53 by rserban           #+#    #+#             */
/*   Updated: 2014/11/15 15:09:51 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *node;
	t_list *temp;

	node = NULL;
	while (lst)
	{
		temp = f(lst);
		if (temp == NULL)
			return (NULL);
		ft_lstadd_end(&node, temp);
		lst = lst->next;
	}
	return (node);
}
