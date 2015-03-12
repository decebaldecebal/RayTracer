/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuresan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 19:07:21 by lmuresan          #+#    #+#             */
/*   Updated: 2015/03/12 16:34:30 by lmuresan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static void		determine_color(t_env *e, t_vec3 *pi, t_obj *obj)
{
	int		i;

	i = 0;
	while (e->lights && e->lights[i])
	{
		check_objects(e, e->lights[i], obj, pi);
		i++;
	}
	if (i == 0)
		set_color(e->color, obj->mat->color.r * AMB_LIGHT,
			obj->mat->color.g * AMB_LIGHT, obj->mat->color.b * AMB_LIGHT);
}

void			determine_pi(t_env *e, t_vec3 *pi, t_obj *temp, double *dist)
{
	add_vector(pi, e->ray->ori, multiply_vector_value(pi, e->ray->dir,
			*dist));
	determine_color(e, pi, temp);
}

static void		apply_antialiasing_set_color(t_env *e)
{
	e->color->r /= e->aliasingsq;
	e->color->g /= e->aliasingsq;
	e->color->b /= e->aliasingsq;
}

t_obj			*apply_antialiasing(t_env *e, int x, int y, double *dist)
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
	apply_antialiasing_set_color(e);
	return (prim);
}
