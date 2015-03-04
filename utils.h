/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:11:15 by rserban           #+#    #+#             */
/*   Updated: 2015/03/04 18:13:49 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct	s_vec3
{
	float x;
	float y;
	float z;
}				t_vec3;

typedef struct	s_ray
{
	t_vec3 *ori;
	t_vec3 *dir;
}				t_ray;

typedef struct	s_camera
{
	t_vec3 *campos;
	t_vec3 *camdir;
	t_vec3 *camright;
	t_vec3 *camdown;
}				t_camera;

#endif
