/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 11:53:35 by rserban           #+#    #+#             */
/*   Updated: 2015/03/05 15:53:37 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_obj		*new_object(t_shape type, t_vec3 *normal, void *object, t_mat *mat)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (!obj)
		mem_error();
	obj->obj = object;
	obj->normal = normal;
	obj->mat = mat;
	obj->type = type;
	return (obj);
}

t_plane		*new_plane(float d)
{
	t_plane *plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		mem_error();
	plane->d = d;
	return (plane);
}

t_sphere	*new_sphere(float radius, int light)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		mem_error();
	sphere->radius = radius;
	sphere->light = light;
	sphere->sqradius = radius * radius;
	return (sphere);
}

t_cylinder	*new_cylinder(t_vec3 *dir, float radius, float length)
{
	t_cylinder *cyl;

	cyl = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cyl)
		mem_error();
	cyl->dir = dir;
	cyl->radius = radius;
	cyl->sqradius = radius * radius;
	cyl->length = length;
	return (cyl);
}

t_cone		*new_cone(t_vec3 *dir, float angle)
{
	t_cone *cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
	if (!cone)
		mem_error();
	cone->dir = dir;
	cone->cosp = pow(cos(angle * (PI / 180)), 2);
	cone->sinp = pow(sin(angle * (PI / 180)), 2);
	return (cone);
}
