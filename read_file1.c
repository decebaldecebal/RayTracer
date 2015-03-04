/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:25:34 by rserban           #+#    #+#             */
/*   Updated: 2015/03/04 18:46:23 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	read_camera(int f, t_env *e, char **line)
{
	char	**numbers;
	t_vec3	*campos;
	t_vec3	*lookat;

	while (get_next_line(f, line) > 0 &&
			ft_strcmp(*line, "****") != 0)
	{
		numbers = ft_strsplit(*line, ' ');
		if (!ft+strcmp(numbers[0], "pos:"))
			campos = create_vector(ft_at_double(numbers[1]),
				ft_at_double(numbers[2]), ft_at_double(numbers[3]));
		if (!ft+strcmp(numbers[0], "dir:"))
			lookat = create_vector(ft_at_double(numbers[1]),
				ft_at_double(numbers[2]), ft_at_double(numbers[3]));
		free(numbers);
		numbers = NULL;
	}
	e->view.cam = new_camera(campos, lookat);
}

void	read_file(t_env *e, char *file)
{
	char	*line;
	int		f;

	f = open(file, O_RDONLY);
	if (f < 0)
	{
		ft_putstr("Can not read file.\n");
		exit(0);
	}
	while (get_next_line(f, &line) > 0)
	{
		if (!ft_strcmp(f, ret, "camera:"))
			read_camera(e, &line);
	}
}
