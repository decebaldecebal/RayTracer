/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 16:53:30 by rserban           #+#    #+#             */
/*   Updated: 2015/03/08 14:01:16 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	check_color(t_color *c)
{
	if (c->r > 255)
		c->r = 255;
	if (c->g > 255)
		c->g = 255;
	if (c->b > 255)
		c->b = 255;
	if (c->r < 0)
		c->r = 0;
	if (c->g < 0)
		c->g = 0;
	if (c->b < 0)
		c->b = 0;
}

void	set_color(t_color *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

void	put_pixel_to_img(t_env *e, t_color *color, int x, int y)
{
    int i;

    i = (WIN_HEIGHT - y - 1) * WIN_WIDTH + x;
	check_color(color);
	e->img[i].r = color->r;
	e->img[i].g = color->g;
	e->img[i].b = color->b;
}
