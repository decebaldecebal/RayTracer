/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:17:20 by rserban           #+#    #+#             */
/*   Updated: 2015/03/04 18:46:21 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_camera	*new_camera(t_vec3 *campos, t_vec3 *lookat)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		mem_error();
	cam->campos = campos;
	cam->camdir = norm_vector(substract_vector(lookat, lookat, campos));
	cam->camright = norm_vector(vector_cross(create_vector(0, 1, 0), cam->camdir));
	cam->camdown = vector_cross(cam->camright, cam->camdir);
	return (cam);
}

t_light		*new_light(t_vec3 *pos, t_color color)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		mem_error();
	light->pos = pos;
	light->color.r = color.r;
	light->color.g = color.g;
	light->color.b = color.b;
	return (light);
}
