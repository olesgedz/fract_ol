/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carpet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 20:24:39 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/28 16:58:11 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_pixel	carpet(t_mlx *mlx, int x, int y)
{
	int			i;
	t_complex	c;

	i = 0;
	mlx->cam->scale = (mlx->cam->scale >= 5) ? 1.6 : mlx->cam->scale;
	mlx->cam->scale = (mlx->cam->scale <= 0.6) ? 1.6 : mlx->cam->scale;
	x = (x) / mlx->cam->scale;
	y = (y) / mlx->cam->scale;
	x = ABS(x);
	y = ABS(y);
	c.r = 0;
	c.i = 0;
	while ((x > 0 || y > 0) && i < mlx->n)
	{
		if (x % 3 == 1 && y % 3 == 1)
			return ((t_pixel){.c = c, .i = 0});
		x /= 3;
		y /= 3;
		i++;
	}
	return ((t_pixel){.c = c, .i = 20});
}
