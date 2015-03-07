/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 15:30:24 by rserban           #+#    #+#             */
/*   Updated: 2015/03/07 16:42:15 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void		read_planes(int f, t_env *e, char **line, int *i)
{
	char	**nums;
	t_color	color;

	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "****"))
	{
		nums = ft_strsplit(*line, ' ');
		if (!ft_strcmp(nums[0], "normal:"))
		{
			e->objs[*i] = new_object(plane, create_vector(ft_atof(nums[1]),
					ft_atof(nums[2]), ft_atof(nums[3])), NULL, NULL);
		}
		else if (!ft_strcmp(nums[0], "distance:"))
			e->objs[*i]->obj = new_plane(ft_atof(nums[1]));
		else if (!ft_strcmp(nums[0], "color:"))
			set_color(&color, ft_atoi(nums[1]), ft_atoi(nums[2]), ft_atoi(nums[3]));
		else if (!ft_strcmp(nums[0], "diffuse:"))
			e->objs[(*i)++]->mat = new_material(&color, ft_atof(nums[1]));

	}
}

void		read_spheres(int f, t_env *e, char **line, int *i)
{
	char	**nums;
	t_color	color;

	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "****"))
	{
		nums = ft_strsplit(*line, ' ');
		if (!ft_strcmp(nums[0], "center:"))
		{
			e->objs[*i] = new_object(sphere, create_vector(ft_atof(nums[1]),
					ft_atof(nums[2]), ft_atof(nums[3])), NULL, NULL);
		}
		else if (!ft_strcmp(nums[0], "radius:"))
			e->objs[*i]->obj = new_sphere(ft_atof(nums[1]));
		else if (!ft_strcmp(nums[0], "color:"))
			set_color(&color, ft_atoi(nums[1]), ft_atoi(nums[2]), ft_atoi(nums[3]));
		else if (!ft_strcmp(nums[0], "diffuse:"))
			e->objs[(*i)++]->mat = new_material(&color, ft_atof(nums[1]));
		}
}
