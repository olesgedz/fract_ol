/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:26:20 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/01 23:21:04 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <time.h>

int					ft_mouse_release(int button, int x, int y, t_mlx *mlx)
{
	y = button && x && y;
	mlx->mouse->isdown = FALSE;
	return (0);
}

static void			ft_change_coef(int x, int y, t_mlx *mlx)
{
	mlx->clock_prg = clock();
	x -= WIN_WIDTH / 2;
	y -= WIN_HEIGHT / 2;
	mlx->data->fractal[mlx->data->nfractal].ca = ((float)x / WIN_WIDTH) * 2;
	mlx->data->fractal[mlx->data->nfractal].cb = ((float)y / WIN_HEIGHT) * 2;
	ft_render(mlx);
}

int					ft_inrange(int x, int y)
{
	if (0 <= x && x <= FRAC_W &&\
		0 <= y && y <= FRAC_H)
		return (1);
	return (0);
}

int					ft_mouse_move(int x, int y, t_mlx *mlx)
{
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (mlx->mouse->isdown == TRUE && ft_inrange(x, y))
	{
		mlx->cam->offsetx -= (x - mlx->mouse->lastx) * 4 / mlx->cam->scale;
		mlx->cam->offsety -= -(y - mlx->mouse->lasty) * 4 / mlx->cam->scale;
		ft_render(mlx);
	}
	if (((FPS) * (clock() - mlx->clock_prg)) / CLOCKS_PER_SEC > 1
	&& mlx->data->c && mlx->data->nfractal != FRACTAL_N - 1)
		ft_change_coef(x, y, mlx);
	else if (((950) * (clock() - mlx->clock_prg)) \
		/ CLOCKS_PER_SEC > 1 && mlx->data->c)
	{
		mlx->clock_prg = clock();
		mlx->data->size_tree = (float)y / FRAC_H;
		mlx->data->size_tree2 = (float)x / FRAC_W;
		ft_render(mlx);
	}
	return (0);
}
