/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:03:38 by rserban           #+#    #+#             */
/*   Updated: 2015/03/08 12:46:36 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	calculate_reflection(t_env *e, t_vec3 *pi, t_obj *temp, int depth)
{
	float	rd[2];
	t_vec3	norm;
	t_vec3	vec;
	t_vec3	vec2;
	t_color	c;

	rd[0] = temp->mat->refl;
	if (rd[0] > 0 && depth < TRACE_DEPTH)
	{
		set_color(&c, e->color->r, e->color->g, e->color->b);
		get_normal(&norm, temp, pi);
		substract_vector(&vec, e->ray->dir, multiply_vector_value(&vec,
				&norm, 2.0f * vector_dot(e->ray->dir, &norm)));
		if (e->ray)
			free(e->ray);
		e->ray = new_ray(add_vector(&vec2, pi, multiply_vector_value(&vec2,
				&vec, EPSILON)), &vec);
		ray_trace(e, depth + 1, &rd[1]);
		e->color->r = c.r + rd[0] * e->color->r * temp->mat->color.r / 255;
		e->color->g = c.g + rd[0] * e->color->g * temp->mat->color.g / 255;
		e->color->b = c.b + rd[0] * e->color->b * temp->mat->color.b / 255;
	}
}
