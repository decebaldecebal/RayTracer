/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:17:22 by rserban           #+#    #+#             */
/*   Updated: 2015/03/09 18:20:55 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static int	intersect_plane(t_obj *p, t_ray *ray, double *dist)
{
	double d;
	double dd;

	d = vector_dot(p->normal, ray->dir);
	if (d != 0)
	{
		dd = -(vector_dot(p->normal, ray->ori) + ((t_plane *)p->obj)->d) / d;
		if (dd > 0 && dd < *dist)
		{
			*dist = dd;
			return (1);
		}
	}
	return (0);
}

static int	intersect_sphere(t_obj *s, t_ray *ray, double *dist)
{
	t_vec3		vec;
	t_sphere	*temp;
	double		b;
	double		det;

	temp = (t_sphere *)s->obj;
	substract_vector(&vec, ray->ori, s->normal);
	b = -vector_dot(&vec, ray->dir);
	det = (b * b) - vector_dot(&vec, &vec) + temp->sqradius;
	if (det > 0 && (det = sqrtf(det)))
	{
		if (b + det > 0 && b - det < 0 && b + det < *dist)
		{
			*dist = b + det;
			return (-1);
		}
		else if (b + det > 0 && b - det >= 0 && b - det < *dist)
		{
			*dist = b - det;
			return (1);
		}
	}
	return (0);
}

static int	intersect_cylinder(t_obj *o, t_ray *ray, double *dist)
{
	t_cylinder	*temp;
	t_vec3		delta;
	t_vec3		vec;
	t_vec3		vec2;
	double		rslt[2];

	temp = ((t_cylinder *)o->obj);
	substract_vector(&delta, ray->ori, o->normal);
	substract_vector(&vec, ray->dir, multiply_vector_value(&vec, temp->dir,
				vector_dot(ray->dir, temp->dir)));
	substract_vector(&vec2, &delta, multiply_vector_value(&vec2, temp->dir,
				vector_dot(&delta, temp->dir)));
	rslt[0] = solve_equation(vector_dot(&vec, &vec), 2 * vector_dot(&vec,
				&vec2), (vector_dot(&vec2, &vec2) - temp->sqradius), &rslt[1]);
	if (rslt[0] && rslt[1] < *dist)
	{
		*dist = rslt[1];
		return (rslt[0]);
	}
	return (0);
}

static int	intersect_cone(t_obj *co, t_ray *ray, double *dist)
{
	t_cone	*temp;
	t_vec3	vec;
	t_vec3	vec2;
	t_vec3	delta;
	double	rslt[2];

	temp = ((t_cone *)co->obj);
	substract_vector(&delta, ray->ori, co->normal);
	substract_vector(&vec, ray->dir, multiply_vector_value(&vec, temp->dir,
				vector_dot(ray->dir, temp->dir)));
	substract_vector(&vec2, &delta, multiply_vector_value(&vec2, temp->dir,
				vector_dot(&delta, temp->dir)));
	rslt[0] = solve_equation(temp->cosp * vector_dot(&vec, &vec) -
			temp->sinp * pow(vector_dot(ray->dir, temp->dir), 2),
			2 * (temp->cosp * vector_dot(&vec, &vec2) - temp->sinp *
			vector_dot(ray->dir, temp->dir) * vector_dot(&delta, temp->dir)),
			temp->cosp * vector_dot(&vec2, &vec2) - temp->sinp *
			pow(vector_dot(&delta, temp->dir), 2), &rslt[1]);
	if (rslt[0] && rslt[1] < *dist)
	{
		*dist = rslt[1];
		return (rslt[0]);
	}
	return (0);
}

int			intersect_primitive(t_obj *obj, t_ray *ray, double *dist)
{
	int result;

	result = 0;
	if (obj->type == plane)
		result = intersect_plane(obj, ray, dist);
	else if (obj->type == sphere)
		result = intersect_sphere(obj, ray, dist);
	else if (obj->type == cyl)
		result = intersect_cylinder(obj, ray, dist);
	else if (obj->type == cone)
		result = intersect_cone(obj, ray, dist);
	return (result);
}
