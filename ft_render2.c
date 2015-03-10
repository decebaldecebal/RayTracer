/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:03:38 by rserban           #+#    #+#             */
/*   Updated: 2015/03/10 17:11:05 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void		calculate_reflection(t_env *e, t_vec3 *pi, t_obj *temp, int depth)
{
	double	rd[2];
	t_vec3	norm;
	t_vec3	vec;
	t_vec3	vec2;
	t_color	c;

	rd[0] = temp->mat->refl;
	if (rd[0] > 0.0f && depth < TRACE_DEPTH)
	{
		set_color(&c, e->color->r, e->color->g, e->color->b);
		set_color(e->color, 0, 0, 0);
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

static void	set_color_aux(t_env *e, t_local *l, t_obj *temp)
{
	set_color(&l->c[1],
			expf(temp->mat->color.r * 0.15f * (-l->nd[1])),
			expf(temp->mat->color.g * 0.15f * (-l->nd[1])),
			expf(temp->mat->color.b * 0.15f * (-l->nd[1])));
	set_color(e->color,
			l->c[0].r + e->color->r * l->c[1].r,
			l->c[0].g + e->color->g * l->c[1].g,
			l->c[0].b + e->color->b * l->c[1].b);
}

static void	add_vector_aux(t_env *e, t_local *l)
{
	add_vector(&l->vec[1],
			multiply_vector_value(&l->vec[1], e->ray->dir, l->nd[0]),
			multiply_vector_value(&l->vec[1], &l->vec[0], l->nd[0] * l->cos[0] -
				sqrtf(l->cos[1])));
}

void		calculate_refraction(t_env *e, t_vec3 *pi, t_obj *temp,
		double par[3])
{
	t_local l;

	l.refr[0] = temp->mat->refr;
	if (l.refr[0] > 0.0f && par[0] < TRACE_DEPTH)
	{
		l.refr[1] = temp->mat->refrind;
		l.nd[0] = par[1] / l.refr[1];
		get_normal(&l.vec[0], temp, pi);
		multiply_vector_value(&l.vec[0], &l.vec[0], par[2]);
		l.cos[0] = -vector_dot(&l.vec[0], e->ray->dir);
		l.cos[1] = 1.0f - l.nd[0] * l.nd[0] * (1.0f - l.cos[0] * l.cos[0]);
		if (l.cos[1] > 0.0f)
		{
			add_vector_aux(e, &l);
			if (e->ray)
				free(e->ray);
			e->ray = new_ray(add_vector(&l.vec[2], pi,
						multiply_vector_value(&l.vec[2], &l.vec[1], EPSILON)),
					&l.vec[1]);
			set_color(&l.c[0], e->color->r, e->color->g, e->color->b);
			set_color(e->color, 0, 0, 0);
			ray_trace(e, par[0] + 1, l.refr[1], &l.nd[1]);
			set_color_aux(e, &l, temp);
		}
	}
}

t_obj		*apply_antialiasing(t_env *e, int x, int y, double *dist)
{
	int		txy[2];
	float	sx;
	float	sy;
	int		xy[2];
	t_obj	*prim;

	prim = NULL;
	txy[0] = -1;
	xy[0] = x;
	xy[1] = y;
	while (++txy[0] < ANTIALIASING)
	{
		txy[1] = -1;
		while (++txy[1] < ANTIALIASING)
		{
			get_sx_sy_aliasing(&sx, &sy, xy, txy);
			if (e->ray)
				free(e->ray);
			e->ray = make_ray(e, sx, sy);
			prim = ray_trace(e, 1, 1.0f, dist);
		}
	}
	e->color->r /= e->aliasingsq;
	e->color->g /= e->aliasingsq;
	e->color->b /= e->aliasingsq;
	return (prim);
}
