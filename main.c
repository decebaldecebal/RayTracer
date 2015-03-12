/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 11:34:22 by rserban           #+#    #+#             */
/*   Updated: 2015/03/12 16:29:14 by lmuresan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_mat		*new_material(t_color *c, float diff, float refl, float refr[2])
{
	t_mat *mat;

	mat = (t_mat *)malloc(sizeof(t_mat));
	if (!mat)
		mem_error();
	mat->color.r = c->r;
	mat->color.g = c->g;
	mat->color.b = c->b;
	mat->diff = diff;
	mat->spec = 1.0f - diff;
	mat->refl = refl;
	mat->refr = refr[0];
	mat->refrind = refr[1];
	return (mat);
}

static int	key_hook(int key, t_env *e)
{
	if (key == 65307)
		exit(0);
	if (e->img == NULL)
		return (1);
	return (1);
}

static int	expose_hook(t_env *e)
{
	int i;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		if (e->img[i] != NULL)
			mlx_put_image_to_window(e->mlx, e->win, e->img[i], 0, i);
		i++;
	}
	return (1);
}

void		init_var(t_env *e)
{
	e->last_prim = NULL;
	e->txy[0] = ANTIALIASING / 2;
	e->txy[1] = ANTIALIASING / 2;
}

int			main(int ac, char **av)
{
	t_env	e;
	float	sx;
	float	sy;
	int		xy[2];

	if (ac == 2 && (xy[1] = -1))
	{
		init_var(&e);
		e.objs = NULL;
		e.lights = NULL;
		e.aliasingsq = ANTIALIASING * ANTIALIASING;
		read_file(&e, av[1], 0, 0);
		if (!e.objs)
			mem_error();
		e.color = (t_color *)malloc(sizeof(t_color));
		if (!e.color)
			mem_error();
		e.mlx = mlx_init();
		e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "RTv1");
		mlx_key_hook(e.win, &key_hook, &e);
		mlx_expose_hook(e.win, &expose_hook, &e);
		draw_scene(&e, xy, &sy, &sx);
		mlx_loop(e.mlx);
	}
	return (0);
}
