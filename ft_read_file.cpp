/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:25:34 by rserban           #+#    #+#             */
/*   Updated: 2015/03/08 13:08:36 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static void	read_camera(FILE *f, t_env *e)
{
	char	**nums;
	t_vec3	*campos;
	t_vec3	*lookat;
	char    line[256];

	while (fgets(line, 256, f) && !strstr(line, "****"))
	{
		if (populate_array(line, &nums))
		{
			if (!strcmp(nums[0], "pos:"))
				campos = create_vector(atof(nums[1]),
						atof(nums[2]), atof(nums[3]));
			else if (!strcmp(nums[0], "dir:"))
				lookat = create_vector(atof(nums[1]),
						atof(nums[2]), atof(nums[3]));
			free_char_array(&nums);
		}
	}
	e->cam = new_camera(campos, lookat);
}

static void	read_lights(FILE *f, t_env *e)
{
	char	**nums;
	char    line[256];
	int     i;

    i = 0;
	while (fgets(line, 256, f) && !strstr(line, "****"))
	{
		if (populate_array(line, &nums))
		{
			if (!strcmp(nums[0], "numbers:"))
			{
				e->lights = (t_light **)malloc(sizeof(t_light *) *
						(atoi(nums[1]) + 1));
				if (!e->lights)
					mem_error();
			}
			else if (!strcmp(nums[0], "pos:"))
			{
				e->lights[i] = new_light(create_vector(atof(nums[1]),
							atof(nums[2]), atof(nums[3])));
			}
			else if (!strcmp(nums[0], "color:"))
				set_color(&(e->lights[i++]->color), atoi(nums[1]),
						atoi(nums[2]), atoi(nums[3]));
			free_char_array(&nums);
		}
	}
	e->lights[i] = NULL;
}

static void	read_objects_nb(t_env *e, char *line)
{
	char	**nums;
	int		i;
	int		n;

	if (populate_array(line, &nums))
	{
		n = atoi(nums[1]) + 1;
		e->objs = (t_obj **)malloc(sizeof(t_obj *) * n);
		free_char_array(&nums);
		if (!e->objs)
			mem_error();
		i = 0;
		while (i < n)
			e->objs[i++] = NULL;
	}
}

void		read_file(t_env *e, char *file)
{
    FILE    *f;
    char    line[256];
	int     i;

	f = fopen(file, "r");
	i = 0;
	if (f == NULL)
	{
		printf("Can not read file.\n");
		exit(-1);
	}
	while (fgets(line, 256, f))
	{
		if (strstr(line, "camera:"))
			read_camera(f, e);
		else if (strstr(line, "lights:"))
			read_lights(f, e);
		else if (strstr(line, "objects:"))
			read_objects_nb(e, line);
		else if (strstr(line, "planes:"))
			read_planes(f, e, &i);
		else if (strstr(line, "spheres:"))
			read_spheres(f, e, &i);
		else if (strstr(line, "cylinders:"))
			read_cylinders(f, e, &i);
		else if (strstr(line, "cones:"))
			read_cones(f, e, &i);
	}
	if (e->objs)
        e->objs[i] = NULL;
}
