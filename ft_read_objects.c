/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 15:30:24 by rserban           #+#    #+#             */
/*   Updated: 2015/03/09 17:14:41 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void			read_planes(int f, t_env *e, char **line, int *i)
{
	char	**nums;

	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "****"))
	{
		if (populate_array(*line, &nums))
		{
			if (!ft_strcmp(nums[0], "normal:"))
				e->objs[*i] = new_object(plane, get_vector(nums), NULL, NULL);
			else if (!ft_strcmp(nums[0], "distance:"))
				e->objs[*i]->obj = new_plane(ft_atof(nums[1]));
			free_char_array(&nums);
		}
		else if (e->objs[*i] && !ft_strcmp(*line, "material:"))
			e->objs[(*i)++]->mat = read_material(f, line);
	}
}

void			read_spheres(int f, t_env *e, char **line, int *i)
{
	char	**nums;

	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "****"))
	{
		if (populate_array(*line, &nums))
		{
			if (!ft_strcmp(nums[0], "center:"))
				e->objs[*i] = new_object(sphere, get_vector(nums), NULL, NULL);
			else if (!ft_strcmp(nums[0], "radius:"))
				e->objs[*i]->obj = new_sphere(ft_atof(nums[1]));
			free_char_array(&nums);
		}
		else if (e->objs[*i] && !ft_strcmp(*line, "material:"))
			e->objs[(*i)++]->mat = read_material(f, line);
	}
}

void			read_cylinders(int f, t_env *e, char **line, int *i)
{
	char	**nums;
	t_vec3	*dir;
	float	radius;

	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "****"))
	{
		if (populate_array(*line, &nums))
		{
			if (!ft_strcmp(nums[0], "center:"))
				e->objs[*i] = new_object(cyl, get_vector(nums), NULL, NULL);
			else if (!ft_strcmp(nums[0], "direction:"))
				dir = get_vector(nums);
			else if (!ft_strcmp(nums[0], "radius:"))
				radius = ft_atof(nums[1]);
			else if (!ft_strcmp(nums[0], "length:"))
				e->objs[*i]->obj = new_cylinder(dir, radius, ft_atof(nums[1]));
			free_char_array(&nums);
		}
		else if (e->objs[*i] && !ft_strcmp(*line, "material:"))
			e->objs[(*i)++]->mat = read_material(f, line);
	}
}

void			read_cones(int f, t_env *e, char **line, int *i)
{
	char	**nums;
	t_vec3	*dir;

	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "****"))
	{
		if (populate_array(*line, &nums))
		{
			if (!ft_strcmp(nums[0], "center:"))
				e->objs[*i] = new_object(cone, get_vector(nums), NULL, NULL);
			else if (!ft_strcmp(nums[0], "direction:"))
				dir = get_vector(nums);
			else if (!ft_strcmp(nums[0], "angle:"))
				e->objs[*i]->obj = new_cone(dir, ft_atof(nums[1]));
			free_char_array(&nums);
		}
		else if (e->objs[*i] && !ft_strcmp(*line, "material:"))
			e->objs[(*i)++]->mat = read_material(f, line);
	}
}
