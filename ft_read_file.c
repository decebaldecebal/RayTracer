/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:25:34 by rserban           #+#    #+#             */
/*   Updated: 2015/03/07 15:06:56 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static void	read_camera(int f, t_env *e, char **line)
{
	char	**nums;
	t_vec3	*campos;
	t_vec3	*lookat;

	while (get_next_line(f, line) > 0 &&
			ft_strcmp(*line, "****") != 0)
	{
		nums = ft_strsplit(*line, ' ');
		if (!ft_strcmp(nums[0], "pos:"))
			campos = create_vector(ft_atof(nums[1]),
				ft_atof(nums[2]), ft_atof(nums[3]));
		else if (!ft_strcmp(nums[0], "dir:"))
			lookat = create_vector(ft_atof(nums[1]),
				ft_atof(nums[2]), ft_atof(nums[3]));
		free_char_array(nums);
		free(nums);
		nums = NULL;
	}
	e->cam = new_camera(campos, lookat);
}

static void	read_lights(int f, t_env *e, char **line)
{
	char	**nums;
	int		i;

	i = 0;
	while (get_next_line(f, line) > 0 &&
			ft_strcmp(*line, "****") != 0)
	{
		nums = ft_strsplit(*line, ' ');
		if (!ft_strcmp(nums[0], "numbers:"))
		{
			e->lights = (t_light **)malloc(sizeof(t_light *) *
					(ft_atoi(nums[1]) + 1));
			if (!e->lights)
				mem_error();
		}
		else if (!ft_strcmp(nums[0], "pos:"))
		{
			e->lights[i] = new_light(create_vector(ft_atof(nums[1]),
					ft_atof(nums[2]), ft_atof(nums[3])));
		}
		else if (!ft_strcmp(nums[0], "color:"))
			set_color(&(e->lights[i++]->color), ft_atoi(nums[1]), ft_atoi(nums[2]),
						ft_atoi(nums[3]));
		free_char_array(nums);
		free(nums);
		nums = NULL;
	}
	e->lights[i] = NULL;
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
		else if (!ft_strcmp(line, "lights:"))
			read_lights(f, e, &line);
	}
}
