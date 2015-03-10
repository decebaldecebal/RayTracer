/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 12:28:41 by rserban           #+#    #+#             */
/*   Updated: 2015/03/10 16:14:14 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	mem_error(void)
{
	ft_putendl("Could not allocate memory.");
	exit(-1);
}

void	get_sx_sy(float *sx, float *sy, int x, int y)
{
	if (WIN_WIDTH > WIN_HEIGHT)
	{
		*sx = ((x + 0.5) / WIN_WIDTH) * ASPECT -
			(((WIN_WIDTH - WIN_HEIGHT) / (float)WIN_HEIGHT) / 2);
		*sy = ((WIN_HEIGHT - y) + 0.5) / WIN_HEIGHT;
	}
	else if (WIN_HEIGHT > WIN_WIDTH)
	{
		*sx = (x + 0.5) / (float)WIN_WIDTH;
		*sy = (((WIN_HEIGHT - y) + 0.5) / WIN_HEIGHT) / ASPECT -
			(((WIN_HEIGHT - WIN_WIDTH) / (float)WIN_WIDTH) / 2);
	}
	else
	{
		*sx = (x + 0.5) / WIN_WIDTH;
		*sy = ((WIN_HEIGHT - y) + 0.5) / WIN_HEIGHT;
	}
}

void	put_pixel_to_img(t_env *e, int x, int y, int i)
{
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;

	check_color(e->color);
	data = mlx_get_data_addr(e->img[i], &bpp, &sizeline, &endian);
	if (endian)
	{
		data[(y * sizeline) + x * (bpp / 8)] =
			mlx_get_color_value(e->mlx, e->color->r);
		data[(y * sizeline) + x * (bpp / 8) + 1] =
			mlx_get_color_value(e->mlx, e->color->g);
		data[(y * sizeline) + x * (bpp / 8) + 2] =
			mlx_get_color_value(e->mlx, e->color->b);
	}
	else
	{
		data[(y * sizeline) + x * (bpp / 8)] =
			mlx_get_color_value(e->mlx, e->color->b);
		data[(y * sizeline) + x * (bpp / 8) + 1] =
			mlx_get_color_value(e->mlx, e->color->g);
		data[(y * sizeline) + x * (bpp / 8) + 2] =
			mlx_get_color_value(e->mlx, e->color->r);
	}
}

void	get_normal(t_vec3 *v, t_obj *o, t_vec3 *vec)
{
	t_vec3	temp;

	if (o->type == sphere)
	{
		norm_vector(substract_vector(v, vec, o->normal));
	}
	else if (o->type == cyl)
	{
		substract_vector(&temp, o->normal, vec);
		project_vector(v, &temp, ((t_cylinder *)o->obj)->dir);
		substract_vector(v, v, &temp);
		norm_vector(v);
	}
	else if (o->type == cone)
		get_cone_normal(v, o, vec);
	else
		norm_vector(new_vector(v, o->normal->x, o->normal->y, o->normal->z));
}

int		solve_equation(double a, double b, double c, double *rslt)
{
	double	det;

	det = (b * b) - 4 * a * c;
	if (det > 0 && (det = sqrtf(det)))
	{
		b = -b;
		if (b + det > 0)
		{
			*rslt = (b - det) / (2 * a) - 0.000001;
			if (*rslt < 0)
			{
				*rslt = (b + det) / (2 * a) - 0.000001;
				return (-1);
			}
			return (1);
		}
	}
	return (0);
}
