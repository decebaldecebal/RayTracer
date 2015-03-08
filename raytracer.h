/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 11:32:23 by rserban           #+#    #+#             */
/*   Updated: 2015/03/08 15:25:45 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "utils.h"
# include "objects.h"
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define ASPECT WIN_WIDTH / WIN_HEIGHT

# define TRACE_DEPTH 4
# define AMB_LIGHT 0.4

# define PI 3.14159265359
# define EPSILON 0.0001f

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img[WIN_HEIGHT];
	t_color		*color;
	t_ray		*ray;
	t_obj		**objs;
	t_light		**lights;
	t_camera	*cam;
}				t_env;

/*
** main.c
*/
t_mat			*new_material(t_color *c, float diff, float refl);

/*
** ft_read_file.c
*/
void			read_file(t_env *e, char *file, int f, int i);
int				populate_array(char *line, char ***nums);

/*
** ft_read_objects.c
*/
void			read_planes(int f, t_env *e, char **line, int *i);
void			read_spheres(int f, t_env *e, char **line, int *i);
void			read_cylinders(int f, t_env *e, char **line, int *i);
void			read_cones(int f, t_env *e, char **line, int *i);

/*
** ft_read_utils.c
*/
t_vec3			*get_vector(char **nums);
t_mat			*read_material(int f, char **line);

/*
** ft_render.c
*/
t_obj			*ray_trace(t_env *e, int depth, float refrind, float *dist);
void			draw_scene(t_env *e, int x, int y);

/*
** ft_render2.c
*/
void			calculate_reflection(t_env *e, t_vec3 *pi, t_obj *temp,
				int depth);
void			calculate_refraction(t_env *e, t_vec3 *pi, t_obj *temp,
				float par[2]);
t_obj			*apply_supersampling(t_env *e, int x, int y, float *dist);

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
int				intersect_primitive(t_obj *obj, t_ray *ray, float *dist);

/*
** ft_utils.c
*/
void			mem_error(void);
void			get_sx_sy(float *sx, float *sy, float x, float y);
void			put_pixel_to_img(t_env *e, int x, int y, int i);
void			get_normal(t_vec3 *v, t_obj *o, t_vec3 *vec);
float			solve_equation(float a, float b, float c);

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
void			set_color_mat(t_color *c, float value, t_color mat, t_color l);

/*
** ft_free.c
*/
void			free_char_array(char ***array);

#endif
