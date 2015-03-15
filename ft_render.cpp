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
	while (e->lights && e->lights[i])
	{
		check_objects(e, e->lights[i], obj, pi);
		i++;
	}
	if (i == 0)
		set_color(e->color, obj->mat->color.r * AMB_LIGHT,
			obj->mat->color.g * AMB_LIGHT, obj->mat->color.b * AMB_LIGHT);
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
	i = 0;
	while (e->objs[i])
	{
		if ((res = intersect_primitive(e->objs[i], e->ray, dist)))
		{
			temp = e->objs[i];
			d_r_value[2] = res;
		}
		i++;
	}
	if (temp)
	{
		add_vector(&pi, e->ray->ori, multiply_vector_value(&pi, e->ray->dir,
			*dist));
		determine_color(e, &pi, temp);
		calculate_reflection(e, &pi, temp, depth);
		d_r_value[0] = depth;
		d_r_value[1] = refrind;
		calculate_refraction(e, &pi, temp, d_r_value);
		return (temp);
	}
	return (NULL);
}

void			draw_scene(t_env *e)
{
	double		dist;
	float       sx;
	float		sy;
	t_obj		*last_prim;
	t_obj		*prim;
	int			xy[2];
	int			txy[2];
	float progres;

	last_prim = NULL;
	txy[0] = ANTIALIASING / 2;
	txy[1] = ANTIALIASING / 2;
	for (int x = 0; x < WIN_WIDTH; x++)
    {
        for (int y = 0; y < WIN_HEIGHT; y++)
        {
			xy[0] = x;
			xy[1] = y;
			set_color(e->color, 0, 0, 0);
			get_sx_sy_aliasing(&sx, &sy, xy, txy);
			e->ray = make_ray(e, sx, sy);
			prim = ray_trace(e, 1, 1.0f, &dist);
			if (prim != last_prim || SUPERSAMPLING)
			{
				last_prim = prim;
				set_color(e->color, 0, 0, 0);
				prim = apply_antialiasing(e, x, y, &dist);
			}
			put_pixel_to_img(e, x, y);
			if (e->ray)
				free(e->ray);
		}
		progres = ((float)x / (float)WIN_WIDTH) * 100;
		if ((int)progres == progres)
            cout<<setprecision(2)<<fixed<<progres<<"%...\n";
    }
}
