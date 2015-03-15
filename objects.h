/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 13:04:36 by rserban           #+#    #+#             */
/*   Updated: 2015/03/08 14:10:32 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "utils/utils.h"

typedef enum       e_shape
{
	plane,
	sphere,
	cyl,
	cone,
	light
}               t_shape;

typedef struct	s_color
{
	int r;
	int g;
	int b;
}				t_color;

typedef struct	s_mat
{
	t_color		color;
	float		diff;
	float		spec;
	float		refl;
	float		refr;
	float		refrind;
}				t_mat;

typedef	struct	s_obj
{
	t_shape			type;
	t_mat			*mat;
	void			*obj;
	t_vec3			*normal;
}				t_obj;

typedef struct	s_plane
{
	float	d;
}				t_plane;

typedef struct	s_sphere
{
	float	radius;
	float	sqradius;
}				t_sphere;

typedef struct	s_cylinder
{
	t_vec3	*dir;
	float	radius;
	float	sqradius;
	float	length;
}				t_cylinder;

typedef struct	s_cone
{
	t_vec3	*dir;
	float	cosp;
	float	sinp;
}				t_cone;

typedef struct	s_light
{
	t_vec3	*pos;
	t_color	color;
}				t_light;

#endif
