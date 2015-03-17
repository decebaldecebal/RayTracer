/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 11:32:23 by rserban           #+#    #+#             */
/*   Updated: 2015/03/11 17:43:34 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "objects.h"

# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <vector>
# include <cmath>
# include <limits>

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <fcntl.h>

# include <thread>

using namespace std;

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define ASPECT WIN_WIDTH / WIN_HEIGHT

/*
** 0 - disabled
** 1 - enabled
** WARNING: Enabling this will SIGNIFICANTLY increase render time.
*/
# define SUPERSAMPLING 0

/*
** Amount of antialiasing to be applied.
** If supersampling is enabled, this will instead be the supersampling value.
** WARNING: A bigger value will increase render time.
*/
# define ANTIALIASING 4

/*
** How many concurrent threads to use during rendering.
** It is highly recommended to match this with your processor core number for optimum render time.
*/
# define THREADS 2

# define TRACE_DEPTH 4
# define AMB_LIGHT 0.4

# define PI 3.14159265359
# define EPSILON 0.001f

typedef struct	s_env
{
	float		aliasingsq;
	int         totpixels;
	t_color     *img;
	t_obj		**objs;
	t_light		**lights;
	t_camera	*cam;
}				t_env;

typedef struct	s_local
{
	float		refr[2];
	double		nd[2];
	float		cos[2];
	t_vec3		vec[3];
	t_color		c[2];
}				t_local;

/*
** main.c
*/
t_mat			*new_material(t_color *c, float diff, float refl, float refr[2]);

/*
** ft_read_file.c
*/
void			read_file(t_env *e, char *file);
int				populate_array(char *line, char ***nums);

/*
** ft_read_objects.c
*/
void			read_planes(FILE *f, t_env *e, int *i);
void			read_spheres(FILE *f, t_env *e, int *i);
void			read_cylinders(FILE *f, t_env *e, int *i);
void			read_cones(FILE *f, t_env *e, int *i);

/*
** ft_read_utils.c
*/
t_vec3			*get_vector(char **nums);
t_mat			*read_material(FILE *f);

/*
** ft_render.c
*/
t_obj			*ray_trace(t_env *e, t_ray *ray, t_color *color, int depth, float refrind, double *dist);
void			draw_scene(t_env *e, int y, int endy);

/*
** ft_render2.c
*/
void			calculate_reflection(t_env *e, t_ray *ray, t_color *color, t_vec3 *pi, t_obj *temp, float refrind, int depth);
void			calculate_refraction(t_env *e, t_ray *ray, t_color *color, t_vec3 *pi, t_obj *temp, float refrind, int depth, int result);
t_obj			*apply_antialiasing(t_env *e, t_color *color, int x, int y, double *dist);

/*
** ft_scene.c
*/
t_obj			*new_object(t_shape type, t_vec3 *normal, void *object,
		t_mat *mat);
t_plane			*new_plane(float d);
t_sphere		*new_sphere(float radius);
t_cylinder		*new_cylinder(t_vec3 *dir, float radius, float length);
t_cone			*new_cone(t_vec3 *dir, float angle);

/*
** ft_scene2.c
*/
t_ray			*new_ray(t_vec3 *ori, t_vec3 *dir);
t_ray			*make_ray(t_env *e, float sx, float sy);
t_camera		*new_camera(t_vec3 *campos, t_vec3 *lookat);
t_light			*new_light(t_vec3 *pos);

/*
** ft_intersect.c
*/
int				intersect_primitive(t_obj *obj, t_ray *ray, double *dist);

/*
** ft_utils.c
*/
void			mem_error(void);
void			get_sx_sy(float *sx, float *sy, int x, int y);
void			get_normal(t_vec3 *v, t_obj *o, t_vec3 *vec);
int				solve_equation(double a, double b, double c, double *rslt);

/*
** ft_utils2.c
*/
void			get_cone_normal(t_vec3 *v, t_obj *o, t_vec3 *vec);
void			get_sx_sy_aliasing(float *sx, float *sy, int x, int y, int tx, int ty);

/*
** ft_vector.c
*/
t_vec3			*create_vector(float x, float y, float z);
t_vec3			*new_vector(t_vec3 *v, float x, float y, float z);
void			norm_vector(t_vec3 *v);
float			vector_dot(t_vec3 *vec1, t_vec3 *vec2);
t_vec3			*vector_cross(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2);

/*
** ft_vector_math.c
*/
t_vec3			*substract_vector(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2);
t_vec3			*add_vector(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2);
t_vec3			*multiply_vector_value(t_vec3 *v, t_vec3 *vec, float value);
float			vector_length(t_vec3 *vec);
void			project_vector(t_vec3 *vec, t_vec3 *vec1, t_vec3 *vec2);

/*
** ft_color.c
*/
void			check_color(t_color *c);
void			set_color(t_color *c, int r, int g, int b);
void			put_pixel_to_img(t_env *e, t_color *color, int x, int y);

/*
** ft_free.c
*/
void			free_char_array(char ***array);
void            free_ray(t_ray **ray);

#endif
