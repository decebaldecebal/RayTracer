/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 15:50:49 by rserban           #+#    #+#             */
/*   Updated: 2015/03/11 16:05:59 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static float	get_shade(t_env *e, t_vec3 *l_norm, t_vec3 *pi)
{
	t_vec3	vec;
	t_vec3	vec2;
	t_ray	*ray;
	double	tdist;
	int		i;

	tdist = vector_length(l_norm);
	multiply_vector_value(&vec, l_norm, 1.0f / tdist);
	ray = new_ray(add_vector(&vec2, pi, multiply_vector_value(&vec2, &vec,
					EPSILON)), &vec);
	i = 0;
	while (e->objs[i])
	{
		if (intersect_primitive(e->objs[i], ray, &tdist))
			return (0.0f);
		i++;
	}
	if (ray)
		free(ray);
	return (1.0f);
}

void			check_objects(t_env *e, t_light *light, t_obj *obj, t_vec3 *pi)
{
	t_vec3	l_norm;
	t_vec3	norm;
	float	dot;
	float	value;
	float	shade;

	substract_vector(&l_norm, light->pos, pi);
	shade = get_shade(e, &l_norm, pi);
	norm_vector(&l_norm);
	get_normal(&norm, obj, pi);
	if (obj->mat->diff > 0 && shade > 0)
	{
		dot = vector_dot(&l_norm, &norm);
		if (dot > 0 && (value = dot * obj->mat->diff))
			set_color_mat(e->color, value, obj->mat->color, light->color);
	}
	if (obj->mat->spec > 0 && shade > 0)
	{
		dot = vector_dot(e->ray->dir, substract_vector(&norm, &l_norm,
			multiply_vector_value(&norm, &norm, 2.0f *
			vector_dot(&l_norm, &norm))));
		if (dot > 0 && (value = powf(dot, 20) * obj->mat->spec))
			set_color_mat(e->color, value, obj->mat->color, light->color);
	}
}

t_obj			*ray_trace(t_env *e, int depth, float refrind, double *dist)
{
	t_obj	*temp;
	int		i;
	t_vec3	pi;
	double	d_r_value[3];
	int		res;

	temp = NULL;
	*dist = 1000000.0f;
	i = -1;
	while (e->objs[++i])
		if ((res = intersect_primitive(e->objs[i], e->ray, dist)))
		{
			temp = e->objs[i];
			d_r_value[2] = res;
		}
	if (temp)
	{
		determine_pi(e, &pi, temp, dist);
		calculate_reflection(e, &pi, temp, depth);
		d_r_value[0] = depth;
		d_r_value[1] = refrind;
		calculate_refraction(e, &pi, temp, d_r_value);
		return (temp);
	}
	return (NULL);
}

void			draw_scene(t_env *e, int xy[2], float *sy, float *sx)
{
	double		dist;

	while (++xy[1] < WIN_HEIGHT && (xy[0] = -1))
	{
		e->img[xy[1]] = mlx_new_image(e->mlx, WIN_WIDTH, 1);
		while (++xy[0] < WIN_WIDTH)
		{
			set_color(e->color, 0, 0, 0);
			get_sx_sy_aliasing(sx, sy, xy, e->txy);
			e->ray = make_ray(e, *sx, *sy);
			e->prim = ray_trace(e, 1, 1.0f, &dist);
			if (e->prim != e->last_prim || SUPERSAMPLING)
			{
				e->last_prim = e->prim, set_color(e->color, 0, 0, 0);
				e->prim = apply_antialiasing(e, xy[0], xy[1], &dist);
			}
			put_pixel_to_img(e, xy[0], 0, xy[1]);
			if (e->ray)
				free(e->ray);
		}
		mlx_put_image_to_window(e->mlx, e->win, e->img[xy[1]], 0, xy[1]);
	}
}
