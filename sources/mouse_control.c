/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:26:20 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/12 00:54:41 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include <time.h>
int		ft_mouse_release(int button, int x, int y, t_mlx *mlx)
{
	y = button && x && y;
	mlx->mouse->isdown = FALSE;
	return (0);
}

int			ft_mouse_move(int x, int y, t_mlx *mlx)
{
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (mlx->mouse->isdown == TRUE)
	{
		mlx->cam->offsetx -= (x - mlx->mouse->lastx) * 4 / mlx->cam->scale;
		mlx->cam->offsety -= -(y - mlx->mouse->lasty) * 4 / mlx->cam->scale;
		ft_render(mlx);
	}
	if(((FPS) * (clock() - mlx->clock_prg)) / CLOCKS_PER_SEC > 1 && mlx->c )
	{
		mlx->clock_prg = clock();
		x -= WIN_WIDTH / 2;
		y -= WIN_HEIGHT / 2;
		mlx->ca = ((float)x / WIN_WIDTH) * 2;
		mlx->cb = ((float)y / WIN_HEIGHT) * 2;
		ft_render(mlx);
	}
	return (0);
}
