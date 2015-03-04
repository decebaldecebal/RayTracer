/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_math.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:58:19 by rserban           #+#    #+#             */
/*   Updated: 2015/02/01 11:56:47 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	*substract_vector(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2)
{
	v->x = vec1->x - vec2->x;
	v->y = vec1->y - vec2->y;
	v->z = vec1->z - vec2->z;
	return (v);
}

t_vec3	*add_vector(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2)
{
	v->x = vec1->x + vec2->x;
	v->y = vec1->y + vec2->y;
	v->z = vec1->z + vec2->z;
	return (v);
}

t_vec3	*multiply_vector_value(t_vec3 *v, t_vec3 *vec, float value)
{
	v->x = vec->x * value;
	v->y = vec->y * value;
	v->z = vec->z * value;
	return (v);
}

float	vector_length(t_vec3 *vec)
{
	return (sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}

void	project_vector(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2)
{
	multiply_vector_value(v, vec2, (vector_dot(vec1, vec2) /
				vector_dot(vec2, vec2)));
}
