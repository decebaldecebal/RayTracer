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
	printf("Could not allocate memory.\n");
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

void	put_pixel_to_img(t_env *e, int x, int y)
{
    int i;
    i = (WIN_HEIGHT - y - 1) * WIN_WIDTH + x;

	check_color(e->color);
	e->img[i].r = e->color->r;
	e->img[i].g = e->color->g;
	e->img[i].b = e->color->b;
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
