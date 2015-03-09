/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 18:11:09 by rserban           #+#    #+#             */
/*   Updated: 2015/03/09 18:18:12 by rserban          ###   ########.fr       */
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
