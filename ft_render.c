/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 15:50:49 by rserban           #+#    #+#             */
/*   Updated: 2015/03/08 12:35:31 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static float	get_shade(t_env *e, t_vec3 *l_norm, t_vec3 *pi)
{
	t_vec3	vec;
	t_vec3	vec2;
	t_ray	*ray;
	float	tdist;
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

static void		check_objects(t_env *e, t_light *light, t_obj *obj, t_vec3 *pi)
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

static void		determine_color(t_env *e, t_vec3 *pi, t_obj *obj)
{
	int		i;

	i = 0;
	while (e->lights[i])
	{
		check_objects(e, e->lights[i], obj, pi);
		i++;
	}
}

void			ray_trace(t_env *e, int depth, float *dist)
{
	t_obj	*temp;
	int		i;
	t_vec3	pi;

	set_color(e->color, 0, 0, 0);
	temp = NULL;
	*dist = 1000000.0f;
	i = 0;
	while (e->objs[i])
	{
		if (intersect_primitive(e->objs[i], e->ray, dist))
			temp = e->objs[i];
		i++;
	}
	if (temp)
	{
		add_vector(&pi, e->ray->ori, multiply_vector_value(&pi, e->ray->dir,
			*dist));
		determine_color(e, &pi, temp);
		calculate_reflection(e, &pi, temp, depth);
	}
}

void			draw_scene(t_env *e, int x, int y)
{
	float		dist;
	float		sy;
	float		sx;

	while (++y < WIN_HEIGHT && (x = -1))
	{
		e->img[y] = mlx_new_image(e->mlx, WIN_WIDTH, 1);
		while (++x < WIN_WIDTH)
		{
			get_sx_sy(&sx, &sy, x, y);
			e->ray = make_ray(e, sx, sy);
			ray_trace(e, 1, &dist);
			put_pixel_to_img(e, x, 0, y);
			if (e->ray)
				free(e->ray);
		}
		mlx_put_image_to_window(e->mlx, e->win, e->img[y], 0, y);
	}
}
