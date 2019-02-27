/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 20:13:07 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/26 21:22:46 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_pixel		julia(t_mlx *mlx, int x, int y)
{
	double	za;
	double	zb;
	double	temp;
	int		i;
	t_complex c;
	za = ((4 * (float)x / FRAC_W - 2) / mlx->cam->scale) + ((mlx->cam->offsetx / FRAC_W));
	zb = ((-4 * (float)y / FRAC_H + 2) / mlx->cam->scale) + ((mlx->cam->offsety / FRAC_H));
	i = 0;
	while (za * za + zb * zb <= 4 && i < mlx->n)
	{
		temp = za;
		za = za * za - zb * zb + mlx->fractal[mlx->nfractal].ca;
		zb = 2 * temp * zb + mlx->fractal[mlx->nfractal].cb;
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}

void			ft_image_set_pixel_tree(t_image *image, int x, int y, int color)
{
	if (y >= 0 && x >= 0 && y < FRAC_H && x < FRAC_W)
		*(int *)(image->ptr + ((x + y * WIN_WIDTH) * image->bpp)) = color;
}
