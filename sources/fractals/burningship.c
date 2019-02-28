/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 20:20:56 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/28 16:57:06 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

t_pixel		burningship(t_mlx *mlx, int x, int y)
{
	int			i;
	double		za;
	double		zb;
	double		tmp;
	t_complex	c;

	mlx->fractal[mlx->nfractal].ca = 1.5 * (x - FRAC_W / 2) \
		/ (0.5 * mlx->cam->scale * FRAC_W) \
		+ (mlx->cam->offsetx / FRAC_W / 1.30) - 0.5;
	mlx->fractal[mlx->nfractal].cb = \
	(y - FRAC_H / 2) / (0.5 * mlx->cam->scale * FRAC_H)
		- (mlx->cam->offsety / FRAC_H / 1.97);
	za = 0;
	zb = 0;
	i = 0;
	while (za * za + zb * zb <= 4 && i < mlx->n)
	{
		tmp = za;
		za = fabs(tmp * tmp) - zb * zb + mlx->fractal[mlx->nfractal].ca;
		zb = 2 * fabs(tmp * zb) + mlx->fractal[mlx->nfractal].cb;
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}
