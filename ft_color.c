/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 16:53:30 by rserban           #+#    #+#             */
/*   Updated: 2015/03/05 15:19:30 by rserban          ###   ########.fr       */
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

void	set_color_mat(t_color *c, float value, t_color mat, t_color l)
{
	set_color(c, c->r + value * mat.r * l.r / 255,
		c->g + value * mat.g * l.g / 255,
		c->b + value * mat.b * l.b / 255);
}
