/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 15:30:24 by rserban           #+#    #+#             */
/*   Updated: 2015/03/08 11:52:08 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static t_vec3	*get_vector(char **nums)
{
	return (create_vector(ft_atof(nums[1]), ft_atof(nums[2]),
	ft_atof(nums[3])));
}

void			read_planes(int f, t_env *e, char **line, int *i)
{
	char	**nums;
	t_color	color;

	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "****"))
	{
		if (populate_array(*line, &nums))
		{
			if (!ft_strcmp(nums[0], "normal:"))
				e->objs[*i] = new_object(plane, get_vector(nums), NULL, NULL);
			else if (!ft_strcmp(nums[0], "distance:"))
				e->objs[*i]->obj = new_plane(ft_atof(nums[1]));
			else if (!ft_strcmp(nums[0], "color:"))
				set_color(&color, ft_atoi(nums[1]), ft_atoi(nums[2]),
						ft_atoi(nums[3]));
			else if (!ft_strcmp(nums[0], "diffuse:"))
				e->objs[(*i)++]->mat = new_material(&color, ft_atof(nums[1]));
			free_char_array(&nums);
		}
	}
}

void			read_spheres(int f, t_env *e, char **line, int *i)
{
	char	**nums;
	t_color	color;

	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "****"))
	{
		if (populate_array(*line, &nums))
		{
			if (!ft_strcmp(nums[0], "center:"))
				e->objs[*i] = new_object(sphere, get_vector(nums), NULL, NULL);
			else if (!ft_strcmp(nums[0], "radius:"))
				e->objs[*i]->obj = new_sphere(ft_atof(nums[1]));
			else if (!ft_strcmp(nums[0], "color:"))
				set_color(&color, ft_atoi(nums[1]), ft_atoi(nums[2]),
						ft_atoi(nums[3]));
			else if (!ft_strcmp(nums[0], "diffuse:"))
				e->objs[(*i)++]->mat = new_material(&color, ft_atof(nums[1]));
			free_char_array(&nums);
		}
	}
}

void			read_cylinders(int f, t_env *e, char **line, int *i)
{
	char	**nums;
	t_vec3	*dir;
	float	radius;
	t_color	color;

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
			else if (!ft_strcmp(nums[0], "color:"))
				set_color(&color, ft_atoi(nums[1]), ft_atoi(nums[2]),
						ft_atoi(nums[3]));
			else if (!ft_strcmp(nums[0], "diffuse:"))
				e->objs[(*i)++]->mat = new_material(&color, ft_atof(nums[1]));
			free_char_array(&nums);
		}
	}
}

void			read_cones(int f, t_env *e, char **line, int *i)
{
	char	**nums;
	t_vec3	*dir;
	t_color	color;

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
			else if (!ft_strcmp(nums[0], "color:"))
				set_color(&color, ft_atoi(nums[1]), ft_atoi(nums[2]),
						ft_atoi(nums[3]));
			else if (!ft_strcmp(nums[0], "diffuse:"))
				e->objs[(*i)++]->mat = new_material(&color, ft_atof(nums[1]));
			free_char_array(&nums);
		}
	}
}
