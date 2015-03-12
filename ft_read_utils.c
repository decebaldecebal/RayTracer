/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:49:47 by rserban           #+#    #+#             */
/*   Updated: 2015/03/12 16:45:11 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_vec3				*get_vector(char **nums)
{
	return (create_vector(ft_atof(nums[1]), ft_atof(nums[2]),
	ft_atof(nums[3])));
}

void				read_material_aux(t_rmat *t)
{
	if (!ft_strcmp(t->nums[0], "color:"))
		set_color(&t->color, ft_atoi(t->nums[1]), ft_atoi(t->nums[2]),
				ft_atoi(t->nums[3]));
	else if (!ft_strcmp(t->nums[0], "diffuse:"))
		t->diffuse = ft_atof(t->nums[1]);
	else if (!ft_strcmp(t->nums[0], "reflection:"))
		t->refl = ft_atof(t->nums[1]);
	else if (!ft_strcmp(t->nums[0], "refraction:"))
		t->refr[0] = ft_atof(t->nums[1]);
	else if (!ft_strcmp(t->nums[0], "refraction_index:"))
		t->refr[1] = ft_atof(t->nums[1]);
}

t_mat				*read_material(int f, char **line)
{
	t_rmat	t;

	t.diffuse = 0.0f;
	t.refl = 0.0f;
	t.refr[0] = 0.0f;
	t.refr[1] = 1.0f;
	set_color(&t.color, 0, 0, 0);
	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "**"))
	{
		if (populate_array(*line, &t.nums))
		{
			read_material_aux(&t);
			free_char_array(&t.nums);
		}
	}
	return (new_material(&t.color, t.diffuse, t.refl, t.refr));
}
