/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 20:29:28 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/01 23:22:39 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

t_pixel				randomf(t_mlx *mlx, int x, int y)
{
	double		za;
	double		zb;
	double		temp;
	int			i;
	t_complex	c;

	za = ((4 * (float)x / FRAC_W - 2) / \
		mlx->cam->scale) + ((mlx->cam->offsetx / FRAC_W));
	zb = ((-4 * (float)y / FRAC_W + 2) / \
		mlx->cam->scale) + ((mlx->cam->offsety / FRAC_W));
	i = 0;
	while (za * za + zb * zb <= 4 && i < mlx->data->n)
	{
		temp = za;
		za = za * za - zb * zb + mlx->data->fractal[mlx->data->nfractal].ca;
		zb = sin(2 * temp * zb + mlx->data->fractal[mlx->data->nfractal].cb);
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}
