/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 18:11:09 by rserban           #+#    #+#             */
/*   Updated: 2015/03/10 16:35:05 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void		get_cone_normal(t_vec3 *v, t_obj *o, t_vec3 *vec)
{
	t_vec3	temp;
	t_vec3	temp2;
	t_cone	*cone;

	cone = (t_cone *)o->obj;
	substract_vector(&temp, o->normal, vec);
	project_vector(v, &temp, cone->dir);
	substract_vector(v, v, &temp);
	if (vector_dot(&temp, cone->dir) < 0)
		vector_cross(&temp2, v, cone->dir);
	else
		vector_cross(&temp2, cone->dir, v);
	vector_cross(v, &temp2, &temp);
	norm_vector(v);
}

void		get_sx_sy_aliasing(float *sx, float *sy, int xy[2], int axy[2])
{
	if (ANTIALIASING == 1)
	{
		get_sx_sy(sx, sy, xy[0], xy[1]);
		return ;
	}
	if (WIN_WIDTH > WIN_HEIGHT)
	{
		*sx = ((xy[0] + (float)axy[0] / ((float)ANTIALIASING - 1)) / 
			WIN_WIDTH) * ASPECT - (((WIN_WIDTH - WIN_HEIGHT) / (float)WIN_HEIGHT)/2); 
		*sy = ((WIN_HEIGHT - xy[1]) + (float)axy[0]/((float)ANTIALIASING - 1)) /
			WIN_HEIGHT;
	}
	else if (WIN_HEIGHT > WIN_WIDTH)
	{
		*sx = ((xy[0] + (float)axy[0] / ((float)ANTIALIASING - 1)) / 
			WIN_WIDTH); 
		*sy = (((WIN_HEIGHT - xy[1]) + (float)axy[0]/((float)ANTIALIASING - 1)) /
			WIN_HEIGHT) / ASPECT - (((WIN_HEIGHT - WIN_WIDTH) / (float)WIN_WIDTH) / 2);
	}
	else
	{
		*sx = ((xy[0] + (float)axy[0] / ((float)ANTIALIASING - 1)) / 
			WIN_WIDTH); 
		*sy = (((WIN_HEIGHT - xy[1]) + (float)axy[0]/((float)ANTIALIASING - 1)) /
			WIN_HEIGHT);
	}
}
