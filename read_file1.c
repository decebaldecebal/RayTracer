/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:25:34 by rserban           #+#    #+#             */
/*   Updated: 2015/03/05 17:30:22 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static void	read_camera(int f, t_env *e, char **line)
{
	char	**numbers;
	t_vec3	*campos;
	t_vec3	*lookat;

	while (get_next_line(f, line) > 0 &&
			ft_strcmp(*line, "****") != 0)
	{
		numbers = ft_strsplit(*line, ' ');
		if (!ft_strcmp(numbers[0], "pos:"))
			campos = create_vector(ft_atof(numbers[1]),
				ft_atof(numbers[2]), ft_atof(numbers[3]));
		if (!ft_strcmp(numbers[0], "dir:"))
			lookat = create_vector(ft_atof(numbers[1]),
				ft_atof(numbers[2]), ft_atof(numbers[3]));
		free(numbers);
		numbers = NULL;
	}
	e->cam = new_camera(campos, lookat);
}

void		read_file(t_env *e, char *file)
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
		if (!ft_strcmp(line, "camera:"))
			read_camera(f, e, &line);
	}
}
