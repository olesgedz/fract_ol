/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 20:26:54 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/01 23:22:33 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_pixel	mandelbrot(t_mlx *mlx, int x, int y)
{
	int			i;
	double		za;
	double		zb;
	double		tmp;
	t_complex	c;

	mlx->data->fractal[mlx->data->nfractal].ca = 1.5 * (x - FRAC_W / 1.5) / (0.5 * mlx->cam->scale * FRAC_W)
		+ (mlx->cam->offsetx / FRAC_W);
	mlx->data->fractal[mlx->data->nfractal].cb = (y * 1.5 - FRAC_H / 1.5) \
		/ (0.5 * mlx->cam->scale * FRAC_H)
		- (mlx->cam->offsety / FRAC_H);
	za = 0;
	zb = 0;
	i = 0;
	while (za * za + zb * zb <= 4 && i < mlx->data->n)
	{
		tmp = za;
		za = tmp * tmp - zb * zb + mlx->data->fractal[mlx->data->nfractal].ca;
		zb = 2 * tmp * zb + mlx->data->fractal[mlx->data->nfractal].cb;
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}
