/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 11:34:22 by rserban           #+#    #+#             */
/*   Updated: 2015/03/05 17:29:10 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static t_mat	*new_material(t_color *c, float diff)
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
	return (mat);
}

static int		key_hook(int key, t_env *e)
{
	if (key == 65307)
		exit(0);
	if (e->img == NULL)
		return (1);
	return (1);
}

static void		init_scene(t_env *e)
{
	t_color c;

	set_color(&c, 100, 80, 80);
	e->objs[0] = new_object(plane, create_vector(0, 1.0f, 0), new_plane(5.0f),
			new_material(&c, 1.0f));
	e->objs[1] = new_object(plane, create_vector(0.4f, 0, 0), new_plane(5.0f),
			new_material(&c, 1.0f));
	set_color(&c, 0, 170, 170);
	e->objs[2] = new_object(sphere, create_vector(5, -1, 6),
			new_sphere(2.5f, 0), new_material(&c, 1.0f));
	e->objs[3] = new_object(sphere, create_vector(-7, -2, 4),
			new_sphere(1, 0), new_material(&c, 1.0f));
	set_color(&c, 180, 180, 180);
	e->objs[4] = new_object(sphere, create_vector(0, 4.5f, 4.5f),
			new_sphere(0.1f, 1), new_material(&c, 0));
	e->objs[5] = new_object(sphere, create_vector(-5, 3.5f, 1),
			new_sphere(0.1f, 1), new_material(&c, 0));
	e->objs[6] = new_object(sphere, create_vector(5, 2, 2),
			new_sphere(0.1f, 1), new_material(&c, 0));
	set_color(&c, 200, 0, 0);
	e->objs[7] = new_object(cylinder, create_vector(9, -1, 3), new_cylinder(
				create_vector(-0.3f, 1, 0), 0.8f, 2), new_material(&c, 0.4f));
	e->objs[8] = new_object(cone, create_vector(-2, 2, 2.2f), new_cone(
				create_vector(0.4f, 1, 0), 15), new_material(&c, 0.8f));
}

int				main(int ac, char **av)
{
	t_env	e;

	if (ac == 2)
	{
		e.objs = (t_obj **)malloc(sizeof(t_obj *) * NR_PRIMITIVES);
		if (!e.objs)
			mem_error();
		read_file(&e, av[1]);
		init_scene(&e);
		e.img = NULL;
		e.color = (t_color *)malloc(sizeof(t_color));
		if (!e.color)
			mem_error();
		e.mlx = mlx_init();
		e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "RTv1");
		mlx_key_hook(e.win, &key_hook, &e);
		ft_putstr("You can edit the scene in the file rtv1.c in the init_scene ");
		ft_putstr("function.\nIf you add more objects, change the value of ");
		ft_putendl("NR_PRIMITIVES in rtv1.h.");
		draw_scene(&e, -1, -1);
		mlx_loop(e.mlx);
	}
	return (0);
}
