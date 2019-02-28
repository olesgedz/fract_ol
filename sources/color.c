/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:18:58 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/28 16:24:04 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlib.h"
#include "fractol.h"
#include <math.h>

t_color		linear_color(t_mlx *mlx, double i, t_palette *p)
{
	double		index;
	double		adjust;
	int			c;

	if (p->cycle)
		index = fmod(i, p->cycle - 1) / (p->cycle - 1);
	else
		index = i / mlx->n;
	c = p->count - 1;
	adjust = fmod(index, 1.0f / c) * c;
	if (mlx->smooth)
	{
		return (clerp((t_color)(p->colors[(int)(index * c) + 1]),
		(t_color)(p->colors[(int)(index * c)]),
		(int)(adjust + 1) - adjust));
	}
	return (clerp((t_color)(p->colors[(int)(index * c) + 1]),
		(t_color)(p->colors[(int)(index * c)]),
		(int)(adjust + 1) - adjust));
}

t_color		smooth_color(t_mlx *mlx, t_pixel p, t_palette *pal)
{
	double i;
	double zn;
	double nu;

	zn = log(p.c.r * p.c.r + p.c.i * p.c.i) / 2.0f;
	nu = log(zn / log(2)) / log(2);
	i = p.i + 1 - nu;
	if (i < 0)
		i = 0;
	return (linear_color(mlx, i, pal));
}

int			get_color(t_pixel p, t_mlx *mlx)
{
	if (p.i >= mlx->n)
		return (0x000000);
	if (mlx->smooth && mlx->nfractal != 4)
		return (smooth_color(mlx, p, mlx->palette + mlx->ncolor).value);
	return (linear_color(mlx, (double)p.i, mlx->palette + mlx->ncolor).value);
}
