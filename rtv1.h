/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 11:32:23 by rserban           #+#    #+#             */
/*   Updated: 2015/03/04 18:49:26 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# include "utils.h"
# include "objects.h"
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>

# define NR_PRIMITIVES 9
# define PI 3.14159265359
# define EPSILON 0.0001f

typedef struct	s_win
{
	float		x1;
	float		x2;
	float		y1;
	float		y2;
	float		dx;
	float		dy;
	t_camera	*cam;
}				t_win;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	t_color	*color;
	t_win	view;
	t_vec3	*ori;
	t_ray	*ray;
	t_obj	**objs;
	t_light	**lights;
}				t_env;

void			draw_scene(t_env *e, int x, int y, float sx);

void			read_file(t_env *e, char *file);

t_obj			*new_object(t_shape type, t_vec3 *normal, void *object,
		t_mat *mat);
t_plane			*new_plane(float d);
t_sphere		*new_sphere(float radius, int light);
t_cylinder		*new_cylinder(t_vec3 *dir, float radius, float length);
t_cone			*new_cone(t_vec3 *dir, float angle);

t_camera		*new_camera(t_vec3 *campos, t_vec3 *lookat);
t_light			*new_light(t_vec3 *pos, t_color color);

int				intersect_primitive(t_obj *obj, t_ray *ray, float *dist);

void			mem_error(void);
t_ray			*new_ray(t_vec3 *ori, t_vec3 *dir);
void			put_pixel_to_img(t_env *e, int x, int y, t_color *c);
void			get_normal(t_vec3 *v, t_obj *o, t_vec3 *vec);
float			solve_equation(float a, float b, float c);

t_vec3			*create_vector(float x, float y, float z);
t_vec3			*new_vector(t_vec3 *v, float x, float y, float z);
void			norm_vector(t_vec3 *v);
float			vector_dot(t_vec3 *vec1, t_vec3 *vec2);
t_vec3			*vector_cross(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2);

t_vec3			*substract_vector(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2);
t_vec3			*add_vector(t_vec3 *v, t_vec3 *vec1, t_vec3 *vec2);
t_vec3			*multiply_vector_value(t_vec3 *v, t_vec3 *vec, float value);
float			vector_length(t_vec3 *vec);
void			project_vector(t_vec3 *vec, t_vec3 *vec1, t_vec3 *vec2);

void			check_color(t_color *c);
void			set_color(t_color *c, int r, int g, int b);
void			set_color_mat(t_color *c, float value, t_color mat, t_color l);

#endif
