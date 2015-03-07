/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:25:34 by rserban           #+#    #+#             */
/*   Updated: 2015/03/07 16:43:18 by rserban          ###   ########.fr       */
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
	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "****"))
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

static void	read_objects_nb(t_env *e, char *line)
{
	char	**nums;
	int		i;
	int		n;

	nums = ft_strsplit(line, ' ');
	n = ft_atoi(nums[1]) + 1;
	e->objs = (t_obj **)malloc(sizeof(t_obj *) * n);
	if (!e->objs)
		mem_error();
	free_char_array(nums);
	free(nums);
	nums = NULL;
	i = 0;
	while (i < n)
		e->objs[i++] = NULL;
}

void		read_file(t_env *e, char *file)
{
	char	*line;
	int		f;
	int		i;

	f = open(file, O_RDONLY);
	if (f < 0)
	{
		ft_putstr("Can not read file.\n");
		exit(0);
	}
	i = 0;
	while (get_next_line(f, &line) > 0)
	{
		if (!ft_strcmp(line, "camera:"))
			read_camera(f, e, &line);
		else if (!ft_strcmp(line, "lights:"))
			read_lights(f, e, &line);
		else if (ft_strstr(line, "objects:"))
			read_objects_nb(e, line);
		else if (!ft_strcmp(line, "planes:"))
			read_planes(f, e, &line, &i);
		else if (!ft_strcmp(line, "spheres:"))
			read_spheres(f, e, &line, &i);
	}
}
