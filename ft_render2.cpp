/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:03:38 by rserban           #+#    #+#             */
/*   Updated: 2015/03/11 16:06:51 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void		calculate_reflection(t_env *e, t_ray *ray, t_color *color, t_vec3 *pi, t_obj *temp, float refrind, int depth)
{
    float   refl;
    double   dist;
    t_ray   *tray;
    t_color tcolor;
	t_vec3	norm;
	t_vec3	vec;
	t_vec3	vec2;

	refl = temp->mat->refl;
	if (refl > 0.0f && depth < TRACE_DEPTH)
	{
		get_normal(&norm, temp, pi);
		substract_vector(&vec, ray->dir, multiply_vector_value(&vec, &norm, 2.0f * vector_dot(ray->dir, &norm)));
		tray = new_ray(add_vector(&vec2, pi, multiply_vector_value(&vec2, &vec, EPSILON)), &vec);
		set_color(&tcolor, 0, 0, 0);
		ray_trace(e, tray, &tcolor, depth + 1, refrind, &dist);
		color->r += refl * tcolor.r * temp->mat->color.r / 255;
		color->g += refl * tcolor.g * temp->mat->color.g / 255;
		color->b += refl * tcolor.b * temp->mat->color.b / 255;
		if (tray)
            	{
        	 	tray->dir = NULL;
                	tray->ori = NULL;
                	free(tray);
            	}
	}
}

void		calculate_refraction(t_env *e, t_ray *ray, t_color *color, t_vec3 *pi, t_obj *temp, float refrind, int depth, int result)
{
    float   refr;
    float   rindex;
    float   n;
    t_vec3  norm;
    t_vec3  vec;
    float   cosI;
    float   cosT2;
    double   dist;
    t_color tcolor;
    t_color trans;
    t_ray   *tray;

	refr = temp->mat->refr;
	if (refr > 0.0f && depth < TRACE_DEPTH)
	{
		rindex = temp->mat->refrind;
		n = refrind / rindex;
		get_normal(&norm, temp, pi);
		multiply_vector_value(&norm, &norm, result);
		cosI = -vector_dot(&norm, ray->dir);
		cosT2 = 1.0f - n * n * (1.0f - cosI * cosI);
		if (cosT2 > 0.0f)
		{
            add_vector(&vec, multiply_vector_value(&vec, ray->dir, n), multiply_vector_value(&norm, &norm, n * cosI - sqrtf(cosT2)));
			tray = new_ray(add_vector(&norm, pi, multiply_vector_value(&norm, &vec, EPSILON)), &vec);
            set_color(&tcolor, 0, 0, 0);
			ray_trace(e, tray, &tcolor, depth + 1, rindex, &dist);
			set_color(&trans, temp->mat->color.r * 0.15f * (-dist), temp->mat->color.g * 0.15f * (-dist), temp->mat->color.b * 0.15f * (-dist));
            set_color(&trans, expf(trans.r), expf(trans.g), expf(trans.b));
			color->r += tcolor.r * trans.r;
			color->g += tcolor.g * trans.g;
			color->b += tcolor.b * trans.b;
			if (tray)
                free(tray);
		}
	}
}

t_obj		*apply_antialiasing(t_env *e, t_color *color, int x, int y, double *dist)
{
	int		tx;
	int     ty;
	float	sx;
	float	sy;
	t_obj	*prim;
	t_ray   *ray;

	prim = NULL;
    tx = - ANTIALIASING / 2;
	while (tx < ANTIALIASING / 2)
	{
		ty = - ANTIALIASING / 2;
		while (ty < ANTIALIASING / 2)
		{
			get_sx_sy_aliasing(&sx, &sy, x, y, tx, ty);
			ray = make_ray(e, sx, sy);
			prim = ray_trace(e, ray, color, 1, 1.0f, dist);
			if (ray)
                free_ray(&ray);
			ty++;
		}
		tx++;
	}
	color->r /= e->aliasingsq;
	color->g /= e->aliasingsq;
	color->b /= e->aliasingsq;
	return (prim);
}
