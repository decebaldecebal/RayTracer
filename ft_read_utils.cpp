/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:49:47 by rserban           #+#    #+#             */
/*   Updated: 2015/03/11 17:25:19 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

int			populate_array(char *line, char ***nums)
{
	if (strchr(line, ' '))
	{
		*nums = ft_strsplit(line, ' ');
		if (*nums)
			return (1);
	}
	return (0);
}

t_vec3		*get_vector(char **nums)
{
	return (create_vector(atof(nums[1]), atof(nums[2]),
	atof(nums[3])));
}

t_mat		*read_material(FILE *f)
{
	char	**nums;
	char    line[256];
	t_color	color;
	float	diffuse;
	float	refl;
	float	refr[2];

	diffuse = 0.0f;
	refl = 0.0f;
	refr[0] = 0.0f;
	refr[1] = 1.0f;
	set_color(&color, 0, 0, 0);
	while (fgets(line, 256, f) && !strstr(line, "**"))
	{
		if (populate_array(line, &nums))
		{
			if (!strcmp(nums[0], "color:"))
				set_color(&color, atoi(nums[1]), atoi(nums[2]),
						atoi(nums[3]));
			else if (!strcmp(nums[0], "diffuse:"))
				diffuse = atof(nums[1]);
			else if (!strcmp(nums[0], "reflection:"))
				refl = atof(nums[1]);
			else if (!strcmp(nums[0], "refraction:"))
				refr[0] = atof(nums[1]);
			else if (!strcmp(nums[0], "refraction_index:"))
				refr[1] = atof(nums[1]);
			free_char_array(&nums);
		}
	}
	return (new_material(&color, diffuse, refl, refr));
}
