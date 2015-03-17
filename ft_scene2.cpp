/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:17:20 by rserban           #+#    #+#             */
/*   Updated: 2015/03/11 16:39:10 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_ray		*new_ray(t_vec3 *ori, t_vec3 *dir)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(ray));
	if (!ray)
		mem_error();
	ray->ori = ori;
	ray->dir = dir;
	return (ray);
}

t_ray		*make_ray(t_env *e, float sx, float sy)
{
	t_camera	*cam;
	t_vec3		*dir;
	t_vec3		temp;

	cam = e->cam;
	dir = create_vector(0, 0, 0);
	add_vector(dir, cam->camdir, add_vector(dir,
		multiply_vector_value(dir, cam->camright, sx - 0.5),
		multiply_vector_value(&temp, cam->camdown, sy - 0.5)));
	norm_vector(dir);
	return (new_ray(create_vector(cam->campos->x, cam->campos->y, cam->campos->z), dir));
}

t_camera	*new_camera(t_vec3 *campos, t_vec3 *lookat)
{
	t_camera	*cam;
	t_vec3		*camright;
	t_vec3		*camdown;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		mem_error();
	camright = create_vector(0, 1, 0);
	camdown = create_vector(1, 0, 0);
	cam->campos = campos;
	substract_vector(lookat, lookat, campos);
	norm_vector(lookat);
	cam->camdir = lookat;
	vector_cross(camright, camright, lookat);
	project_vector(camright, camright, camdown);
	norm_vector(camright);
	cam->camright = camright;
	cam->camdown = vector_cross(camdown, cam->camright, new_vector(camdown,
				-lookat->x, -lookat->y, -lookat->z));
	return (cam);
}

t_light		*new_light(t_vec3 *pos)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		mem_error();
	light->pos = pos;
	return (light);
}
