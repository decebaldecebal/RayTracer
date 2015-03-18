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
	{
		ray->dir = NULL;
		ray->ori = NULL;
        	free(ray);
	}
	return (1.0f);
}

static void		check_objects(t_env *e, t_ray *ray, t_color *color, t_light *light, t_obj *obj, t_vec3 *pi)
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
	if (shade > 0.0f)
    {
        if (obj->mat->diff > 0.0f)
        {
            dot = vector_dot(&l_norm, &norm);
            if (dot > 0.0f)
            {
                value = dot * obj->mat->diff * shade;
                color->r += value * obj->mat->color.r * light->color.r / 255;
                color->g += value * obj->mat->color.g * light->color.g / 255;
                color->b += value * obj->mat->color.b * light->color.b / 255;
            }
        }
        if (obj->mat->spec > 0.0f)
        {
            dot = vector_dot(ray->dir, substract_vector(&l_norm, &l_norm, multiply_vector_value(&norm, &norm, 2.0f * vector_dot(&l_norm, &norm))));
            if (dot > 0)
            {
                value = powf(dot, 20) * obj->mat->spec * shade;
                color->r += value * obj->mat->color.r * light->color.r / 255;
                color->g += value * obj->mat->color.g * light->color.g / 255;
                color->b += value * obj->mat->color.b * light->color.b / 255;
            }
        }
    }
}

static void		determine_color(t_env *e, t_ray *ray, t_color *color, t_vec3 *pi, t_obj *obj)
{
	int		i;

	i = 0;
	while (e->lights && e->lights[i])
	{
		check_objects(e, ray, color, e->lights[i], obj, pi);
		i++;
	}
	if (i == 0)
		set_color(color, obj->mat->color.r * AMB_LIGHT,
			obj->mat->color.g * AMB_LIGHT, obj->mat->color.b * AMB_LIGHT);
}

t_obj			*ray_trace(t_env *e, t_ray *ray, t_color *color, int depth, float refrind, double *dist)
{
	t_obj	*temp;
	int		i;
	t_vec3	pi;
	int		tres;
	int     result;

    if (depth > TRACE_DEPTH)
        return (NULL);
	temp = NULL;
	*dist = 1000000.0f;
	i = 0;
	while (e->objs[i])
	{
		if ((tres = intersect_primitive(e->objs[i], ray, dist)))
		{
			temp = e->objs[i];
			result = tres;
		}
		i++;
	}
	if (temp)
	{
		add_vector(&pi, ray->ori, multiply_vector_value(&pi, ray->dir,
			*dist));
		determine_color(e, ray, color, &pi, temp);
		calculate_reflection(e, ray, color, &pi, temp, refrind, depth);
		calculate_refraction(e, ray, color, &pi, temp, refrind, depth, result);
		return (temp);
	}
	return (NULL);
}

void			draw_scene(t_env *e, int yy, int endy)
{
	double		dist;
	float       sx;
	float		sy;
	t_obj		*last_prim;
	t_obj		*prim;
	float       progres;
	t_ray       *ray;
	t_color     color;

	last_prim = NULL;
	for (int x = 0; x < WIN_WIDTH; x++)
    {
        for (int y = yy; y < endy; y++)
        {
			set_color(&color, 0, 0, 0);
			get_sx_sy_aliasing(&sx, &sy, x, y, 0, 0);
			ray = make_ray(e, sx, sy);
			prim = ray_trace(e, ray, &color, 1, 1.0f, &dist);
			if (prim != last_prim || SUPERSAMPLING)
			{
				last_prim = prim;
				set_color(&color, 0, 0, 0);
				prim = apply_antialiasing(e, &color, x, y, &dist);
			}
			put_pixel_to_img(e, &color, x, y);
			if (ray)
				free_ray(&ray);
		}
		progres = ((float)x / (float)WIN_WIDTH) * 100;
		if ((int)progres == progres)
            cout<<setprecision(2)<<fixed<<progres<<"%...\n";
    }
}
