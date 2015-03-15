/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 11:49:07 by rserban           #+#    #+#             */
/*   Updated: 2015/03/05 15:19:39 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_vec3	*create_vector(float x, float y, float z)
{
	t_vec3	*v;

	v = (t_vec3 *)malloc(sizeof(t_vec3));
	if (!v)
		mem_error();
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

t_vec3	*new_vector(t_vec3 *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

void	norm_vector(t_vec3 *v)
{
	float l;

	l = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x *= l;
	v->y *= l;
	v->z *= l;
}

float	vector_dot(t_vec3 *vec1, t_vec3 *vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y +
	vec1->z * vec2->z);
}

t_vec3	*vector_cross(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2)
{
	v->x = vec1->y * vec2->z - vec1->z * vec2->y;
	v->y = vec1->z * vec2->x - vec1->x * vec2->z;
	v->z = vec1->x * vec2->y - vec1->y * vec2->x;
	return (v);
}
