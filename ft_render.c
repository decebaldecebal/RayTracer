/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 15:50:49 by rserban           #+#    #+#             */
/*   Updated: 2015/03/04 17:45:33 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static float	get_shade(t_env *e, t_obj *light, t_vec3 *l_norm, t_vec3 *pi)
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
	while (i < NR_PRIMITIVES)
	{
		if (!(e->objs[i]->type == sphere && ((t_sphere *)(e->objs[i]->obj))
			->light == 1) && e->objs[i] != light &&
				intersect_primitive(e->objs[i], ray, &tdist))
			return (0.0f);
		i++;
	}
	return (1.0f);
}

static void		check_objects(t_env *e, t_obj *light, t_obj *obj, t_vec3 *pi)
{
	t_vec3	l_norm;
	t_vec3	norm;
	float	dot;
	float	value;
	float	shade;

	substract_vector(&l_norm, light->normal, pi);
	shade = get_shade(e, light, &l_norm, pi);
	norm_vector(&l_norm);
	get_normal(&norm, obj, pi);
	if (obj->mat->diff > 0 && shade > 0)
	{
		dot = vector_dot(&l_norm, &norm);
		if (dot > 0 && (value = dot * obj->mat->diff))
			set_color_mat(e->color, value, obj->mat->color, light->mat->color);
	}
	if (obj->mat->spec > 0 && shade > 0)
	{
		dot = vector_dot(e->ray->dir, substract_vector(&norm, &l_norm,
			multiply_vector_value(&norm, &norm, 2.0f *
			vector_dot(&l_norm, &norm))));
		if (dot > 0 && (value = powf(dot, 20) * obj->mat->spec))
			set_color_mat(e->color, value, obj->mat->color, light->mat->color);
	}
}

static void		determine_color(t_env *e, t_obj *obj, float *dist)
{
	t_vec3	pi;
	t_obj	*temp;
	int		i;

	add_vector(&pi, e->ray->ori, multiply_vector_value(&pi, e->ray->dir,
		*dist));
	i = 0;
	while (i < NR_PRIMITIVES)
	{
		temp = e->objs[i];
		if (temp->type == sphere && ((t_sphere *)temp->obj)->light == 1)
			check_objects(e, temp, obj, &pi);
		i++;
	}
}

static void		ray_trace(t_env *e, float *dist)
{
	t_obj	*temp;
	int		i;

	temp = NULL;
	*dist = 1000000.0f;
	i = 0;
	while (i < NR_PRIMITIVES)
	{
		if (intersect_primitive(e->objs[i], e->ray, dist))
			temp = e->objs[i];
		i++;
	}
	if (temp)
	{
		if (temp->type == sphere && ((t_sphere *)temp->obj)->light == 1)
			set_color(e->color, temp->mat->color.r, temp->mat->color.g,
					temp->mat->color.b);
		else
			determine_color(e, temp, dist);
	}
}

void			draw_scene(t_env *e, int x, int y, float sy)
{
	t_vec3		dir;
	float		dist;
	float		sx;

	while (++y < WIN_HEIGHT && (x = -1))
	{
		e->img = mlx_new_image(e->mlx, WIN_WIDTH, 1);
		sx = e->view.x1;
		while (++x < WIN_WIDTH)
		{
			set_color(e->color, 0, 0, 0);
			substract_vector(&dir, new_vector(&dir, sx, sy, 0), e->ori);
			norm_vector(&dir);
			e->ray = new_ray(e->ori, &dir);
			ray_trace(e, &dist);
			put_pixel_to_img(e, x, 0, e->color);
			if (e->ray)
				free(e->ray);
			sx += e->view.dx;
		}
		mlx_put_image_to_window(e->mlx, e->win, e->img, 0, y);
		free(e->img);
		e->img = NULL;
		sy += e->view.dy;
	}
}
