/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 12:28:41 by rserban           #+#    #+#             */
/*   Updated: 2015/02/01 12:54:32 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	mem_error(void)
{
	ft_putendl("Could not allocate memory.");
	exit(-1);
}

t_ray	*new_ray(t_vec3 *ori, t_vec3 *dir)
{
	t_ray	*r;

	r = (t_ray *)malloc(sizeof(t_ray));
	if (!r)
		mem_error();
	r->ori = ori;
	r->dir = dir;
	return (r);
}

void	put_pixel_to_img(t_env *e, int x, int y, t_color *c)
{
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;

	check_color(e->color);
	data = mlx_get_data_addr(e->img, &bpp, &sizeline, &endian);
	if (endian)
	{
		data[(y * sizeline) + x * (bpp / 8)] =
			mlx_get_color_value(e->mlx, c->r);
		data[(y * sizeline) + x * (bpp / 8) + 1] =
			mlx_get_color_value(e->mlx, c->g);
		data[(y * sizeline) + x * (bpp / 8) + 2] =
			mlx_get_color_value(e->mlx, c->b);
	}
	else
	{
		data[(y * sizeline) + x * (bpp / 8)] =
			mlx_get_color_value(e->mlx, c->b);
		data[(y * sizeline) + x * (bpp / 8) + 1] =
			mlx_get_color_value(e->mlx, c->g);
		data[(y * sizeline) + x * (bpp / 8) + 2] =
			mlx_get_color_value(e->mlx, c->r);
	}
}

void	get_normal(t_vec3 *v, t_obj *o, t_vec3 *vec)
{
	t_vec3	temp;

	if (o->type == sphere)
	{
		norm_vector(substract_vector(v, vec, o->normal));
	}
	else if (o->type == cylinder || o->type == cone)
	{
		substract_vector(&temp, vec, o->normal);
		project_vector(v, &temp, ((t_cylinder *)o->obj)->dir);
		substract_vector(v, &temp, v);
		norm_vector(v);
	}
	else
		norm_vector(new_vector(v, o->normal->x, o->normal->y, o->normal->z));
}

float	solve_equation(float a, float b, float c)
{
	float	det;
	float	rslt;

	det = (b * b) - 4 * a * c;
	if (det > 0 && (det = sqrtf(det)))
	{
		b = -b;
		if (b + det > 0)
		{
			rslt = (b - det) / (2 * a);
			if (rslt < 0)
				rslt = (b + det) / (2 * a);
			return (rslt);
		}
	}
	return (-1);
}
