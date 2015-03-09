/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:03:38 by rserban           #+#    #+#             */
/*   Updated: 2015/03/09 16:42:28 by rserban          ###   ########.fr       */
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
	if (rd[0] > 0.0f && depth < TRACE_DEPTH)
	{
		set_color(&c, e->color->r, e->color->g, e->color->b);
		get_normal(&norm, temp, pi);
		substract_vector(&vec, e->ray->dir, multiply_vector_value(&vec,
				&norm, 2.0f * vector_dot(e->ray->dir, &norm)));
		if (e->ray)
			free(e->ray);
		e->ray = new_ray(add_vector(&vec2, pi, multiply_vector_value(&vec2,
				&vec, EPSILON)), &vec);
		ray_trace(e, depth + 1, 1.0f, &rd[1]);
		e->color->r = c.r + rd[0] * e->color->r * temp->mat->color.r / 255;
		e->color->g = c.g + rd[0] * e->color->g * temp->mat->color.g / 255;
		e->color->b = c.b + rd[0] * e->color->b * temp->mat->color.b / 255;
	}
}

void	calculate_refraction(t_env *e, t_vec3 *pi, t_obj *temp, float par[3])
{
	float	refr[2];
	float 	nd[2];
	float	cos[2];
	t_vec3	vec[3];
	t_color	c[2];

	refr[0] = temp->mat->refr;
	if (refr[0] > 0.0f && par[0] < TRACE_DEPTH)
	{
		refr[1] = temp->mat->refrind;
		nd[0] = par[1] / refr[1];
		get_normal(&vec[0], temp, pi);
		multiply_vector_value(&vec[0], &vec[0], par[2]);
		cos[0] = -vector_dot(&vec[0], e->ray->dir);
		cos[1] = 1.0f - nd[0] * nd[0] * (1.0f - cos[0] * cos[0]);
		if (cos[1] > 0.0f)
		{
			add_vector(&vec[1], multiply_vector_value(&vec[1], e->ray->dir, nd[0]),
			multiply_vector_value(&vec[1], &vec[0], nd[0] * cos[0] - sqrtf(cos[1]))
			);
			if (e->ray)
				free(e->ray);
			e->ray = new_ray(add_vector(&vec[2], pi, multiply_vector_value(&vec[2],
					&vec[1], EPSILON)), &vec[1]);
			set_color(&c[0], e->color->r, e->color->g, e->color->b);
			ray_trace(e, par[0] + 1, refr[1], &nd[1]);
			set_color(&c[1], expf(temp->mat->color.r * 0.15f * (-nd[1])),
				expf(temp->mat->color.g * 0.15f * (-nd[1])),
				expf(temp->mat->color.b * 0.15f * (-nd[1])));
			set_color(e->color, c[0].r + e->color->r * c[1].r,
				c[0].g + e->color->g * c[1].g, c[0].b + e->color->b * c[1].b);
		}
	}
}

t_obj		*apply_supersampling(t_env *e, int x, int y, float *dist)
{
	int		tx;
	int		ty;
	float	sx;
	float	sy;
	t_obj	*prim;

	prim = NULL;
	tx = -1;
	while (tx < 2)
	{
		ty = -1;
		while (ty < 2)
		{
			get_sx_sy(&sx, &sy, (float)x + 0.5 * (float)tx,
					(float)y + 0.5 * (float)ty);
			if (e->ray)
				free(e->ray);
			e->ray = make_ray(e, sx, sy);
			prim = ray_trace(e, 1, 1.0f, dist);
			ty++;
		}
		tx++;
	}
	e->color->r /= 9;
	e->color->g /= 9;
	e->color->b /= 9;
	return (prim);
}
