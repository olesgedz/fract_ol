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

#include "fdf.h"
# include <time.h>
int		ft_mouse_release(int button, int x, int y, t_mlx *mlx)
{
	y = button && x && y;
	mlx->mouse->isdown = FALSE;
	return (0);
}

int		ft_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	y = button && x && y;
	mlx->mouse->isdown = TRUE;
	return (0);
}

// int		ft_mouse_move(int x, int y, t_mlx *mlx)
// {
// 	mlx->mouse->lastx = mlx->mouse->x;
// 	mlx->mouse->lasty = mlx->mouse->y;
// 	mlx->mouse->x = x;
// 	mlx->mouse->y = y;
// 	if (mlx->mouse->isdown == TRUE)
// 	{
// 		mlx->cam->y += (x - mlx->mouse->lastx) * 0.005;
// 		mlx->cam->x += -(y - mlx->mouse->lasty) * 0.005;
// 		ft_render(mlx);
// 	}
// 	return (0);
// }

int			ft_mouse_move(int x, int y, t_mlx *e)
{

	if(((FPS) * (clock() - e->clock_prg)) / CLOCKS_PER_SEC > 1 && e->c )
	{
		e->clock_prg = clock();
		x -= WIN_WIDTH / 2;
		y -= WIN_HEIGHT / 2;
		e->ca = ((float)x / WIN_WIDTH) * 2;
		e->cb = ((float)y / WIN_HEIGHT) * 2;
		ft_render(e);
	}
	return (0);
}
