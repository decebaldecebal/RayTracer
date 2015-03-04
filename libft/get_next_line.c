/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 16:32:33 by rserban           #+#    #+#             */
/*   Updated: 2014/12/03 16:23:52 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void		del_from_list(t_read **start, t_read **val)
{
	t_read		*temp;

	if (*start == *val)
	{
		*start = (*start)->next;
		free((*val)->buf);
		free(*val);
		*val = *start;
	}
	else
	{
		temp = *start;
		while (temp->next != *val)
			temp = temp->next;
		temp->next = (*val)->next;
		free((*val)->buf);
		free(*val);
		*val = temp->next;
	}
}

static t_read	*start_read(int fd)
{
	t_read	*temp;
	char	*buf;
	int		size;

	if (!(temp = (t_read *)malloc(sizeof(t_read))))
		return (NULL);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
	{
		free(temp);
		return (NULL);
	}
	if ((size = read(fd, buf, BUFF_SIZE)) < 0)
	{
		free(temp);
		free(buf);
		return (NULL);
	}
	buf[size] = '\0';
	temp->buf = buf;
	temp->index = 0;
	temp->fd = fd;
	temp->next = NULL;
	return (temp);
}

static int		read_line(int *t, t_read **start, t_read **first, char **line)
{
	char	*buf;
	int		index;

	if (!(buf = (char *)malloc(sizeof(char) * t[0])))
		return (0);
	*line = buf;
	index = (*start)->index;
	while (t[0]--)
	{
		*buf++ = (*start)->buf[index++];
		if ((*start)->buf[index] == '\0')
		{
			del_from_list(first, start);
			while ((*start)->fd != t[1])
				(*start) = (*start)->next;
			index = 0;
		}
	}
	*buf = '\0';
	(*start)->index = index + 1;
	if ((*start)->buf[index + 1] == '\0')
		del_from_list(first, start);
	return (1);
}

static int		get_line_size(int fd, t_read *start)
{
	t_read	*temp;
	int		size;
	int		index;

	index = start->index;
	size = 0;
	while (start->buf[index] != '\n' && start->buf[index] != '\0')
	{
		index++;
		size++;
		if (start->buf[index] == '\0' && index == BUFF_SIZE)
		{
			temp = start;
			while (temp->next)
				temp = temp->next;
			temp->next = start_read(fd);
			if (temp->next == NULL)
				return (-1);
			start = start->next;
			while (start->fd != fd)
				start = start->next;
			index = 0;
		}
	}
	return (size);
}

int				get_next_line(int const fd, char **line)
{
	static t_read	*start;
	t_read			*temp;
	int				t[2];

	if (fd < 0 || (!start && (start = start_read((int)fd)) == NULL))
		return (-1);
	temp = start;
	while (temp->next && temp->fd != fd)
		temp = temp->next;
	if (temp->fd != fd)
	{
		temp->next = start_read((int)fd);
		temp = temp->next;
	}
	if (temp->buf[0] == '\0')
	{
		del_from_list(&start, &temp);
		return (0);
	}
	t[0] = get_line_size((int)fd, temp);
	t[1] = (int)fd;
	if (t[0] == -1 || !read_line(t, &temp, &start, line))
		return (-1);
	return (1);
}
