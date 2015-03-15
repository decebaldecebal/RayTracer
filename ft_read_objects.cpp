/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 15:30:24 by rserban           #+#    #+#             */
/*   Updated: 2015/03/11 16:16:39 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void			read_planes(FILE *f, t_env *e, int *i)
{
	char	**nums;
	char    line[256];

	while (fgets(line, 256, f) && !strstr(line, "****"))
	{
		if (populate_array(line, &nums))
		{
			if (!strcmp(nums[0], "normal:"))
				e->objs[*i] = new_object(plane, get_vector(nums), NULL, NULL);
			else if (!strcmp(nums[0], "distance:"))
				e->objs[*i]->obj = new_plane(atof(nums[1]));
			free_char_array(&nums);
		}
		else if (e->objs[*i] && strstr(line, "material:"))
			e->objs[(*i)++]->mat = read_material(f);
	}
}

void			read_spheres(FILE *f, t_env *e, int *i)
{
	char	**nums;
	char    line[256];

	while (fgets(line, 256, f) && !strstr(line, "****"))
	{
		if (populate_array(line, &nums))
		{
			if (!strcmp(nums[0], "center:"))
				e->objs[*i] = new_object(sphere, get_vector(nums), NULL, NULL);
			else if (!strcmp(nums[0], "radius:"))
				e->objs[*i]->obj = new_sphere(atof(nums[1]));
			free_char_array(&nums);
		}
		else if (e->objs[*i] && strstr(line, "material:"))
			e->objs[(*i)++]->mat = read_material(f);
	}
}

void			read_cylinders(FILE *f, t_env *e, int *i)
{
	char	**nums;
	char    line[256];
	t_vec3	*dir;
	float	radius;

	while (fgets(line, 256, f) && !strstr(line, "****"))
	{
		if (populate_array(line, &nums))
		{
			if (!strcmp(nums[0], "center:"))
				e->objs[*i] = new_object(cyl, get_vector(nums), NULL, NULL);
			else if (!strcmp(nums[0], "direction:"))
				dir = get_vector(nums);
			else if (!strcmp(nums[0], "radius:"))
				radius = atof(nums[1]);
			else if (!strcmp(nums[0], "length:"))
				e->objs[*i]->obj = new_cylinder(dir, radius, atof(nums[1]));
			free_char_array(&nums);
		}
		else if (e->objs[*i] && strstr(line, "material:"))
			e->objs[(*i)++]->mat = read_material(f);
	}
}

void			read_cones(FILE *f, t_env *e, int *i)
{
	char	**nums;
	char    line[256];
	t_vec3	*dir;

	while (fgets(line, 256, f) && !strstr(line, "****\n"))
	{
		if (populate_array(line, &nums))
		{
			if (!strcmp(nums[0], "center:"))
				e->objs[*i] = new_object(cone, get_vector(nums), NULL, NULL);
			else if (!strcmp(nums[0], "direction:"))
				dir = get_vector(nums);
			else if (!strcmp(nums[0], "angle:"))
				e->objs[*i]->obj = new_cone(dir, atof(nums[1]));
			free_char_array(&nums);
		}
		else if (e->objs[*i] && strstr(line, "material:"))
			e->objs[(*i)++]->mat = read_material(f);
	}
}
