/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:49:47 by rserban           #+#    #+#             */
/*   Updated: 2015/03/08 13:19:22 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_vec3		*get_vector(char **nums)
{
	return (create_vector(ft_atof(nums[1]), ft_atof(nums[2]),
	ft_atof(nums[3])));
}

t_mat		*read_material(int f, char **line)
{
	char	**nums;
	t_color	color;
	float	diffuse;
	float	refl;

	diffuse = 0.0f;
	refl = 0.0f;
	set_color(&color, 0, 0, 0);
	while (get_next_line(f, line) > 0 && ft_strcmp(*line, "**"))
	{
		if (populate_array(*line, &nums))
		{
			if (!ft_strcmp(nums[0], "color:"))
				set_color(&color, ft_atoi(nums[1]), ft_atoi(nums[2]),
						ft_atoi(nums[3]));
			else if (!ft_strcmp(nums[0], "diffuse:"))
				diffuse = ft_atof(nums[1]);
			else if (!ft_strcmp(nums[0], "reflection:"))
				refl = ft_atof(nums[1]);
			free_char_array(&nums);
		}
	}
	return (new_material(&color, diffuse, refl));
}
