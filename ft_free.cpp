/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 14:05:14 by rserban           #+#    #+#             */
/*   Updated: 2015/03/08 11:39:20 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static void	free_array_elems(char **array)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}

void		free_char_array(char ***array)
{
	free_array_elems(*array);
	free(*array);
	*array = NULL;
}

void        free_ray(t_ray **ray)
{
    free((*ray)->dir);
    free((*ray)->ori);
    (*ray)->dir = NULL;
    (*ray)->ori = NULL;
    free(*ray);
    *ray = NULL;
}

static void free_object(t_obj *obj)
{
    free(obj->mat);
    obj->mat = NULL;
    free(obj->normal);
    obj->normal = NULL;
    if (obj->type == cyl)
        free(((t_cylinder *)obj->obj)->dir);
    else if (obj->type == cone)
        free(((t_cone *)obj->obj)->dir);
    free(obj->obj);
    obj->obj = NULL;
}

static void free_camera(t_camera *cam)
{
    free(cam->camdir);
    cam->camdir = NULL;
    free(cam->camdown);
    cam->camdown = NULL;
    free(cam->campos);
    cam->campos = NULL;
    free(cam->camright);
    cam->camright = NULL;
}

void        free_environment(t_env *e)
{
    int i;

    i = 0;
    while (e->objs[i])
    {
        free_object(e->objs[i]);
        free(e->objs[i]);
        e->objs[i] = NULL;
        i++;
    }
    free(e->objs);
    e->objs = NULL;
    i = 0;
    while (e->lights[i])
    {
        free(e->lights[i]->pos);
        free(e->lights[i]);
        i++;
    }
    free(e->lights);
    e->lights = NULL;
    free(e->img);
    e->img = NULL;
    free_camera(e->cam);
    free(e->cam);
    e->cam = NULL;
}
