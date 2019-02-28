/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:26:20 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/28 17:57:56 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlib.h"
#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

void				ft_zoom_to_mouse(t_mlx *mlx)
{
	mlx->cam->scale *= 1.1;
	mlx->cam->offsetx += (mlx->mouse->x - FRAC_W / 2) / mlx->cam->scale / 2.51;
	mlx->cam->offsety -= (mlx->mouse->y - FRAC_H / 2) / mlx->cam->scale / 2.51;
}

void				ft_reset_view(t_mlx *mlx)
{
	mlx->cam->scale = 1;
	mlx->cam->offsetx = 0;
	mlx->cam->offsety = 0;
}

int					ft_handle_keys_press(int key, t_mlx *mlx)
{
	mlx->keyboard->keys[key] = TRUE;
	ft_press_move(mlx);
	if (key == B_KEY)
		ft_switch_color(mlx);
	if (key == F_KEY)
		ft_next_fractal(mlx);
	if (key == C_KEY)
		ft_mouse_parameters_switch(mlx);
	if (key == M_KEY)
		ft_switch_smoothing(mlx);
	if (key == R_KEY)
		ft_reset_view(mlx);
	if (key == ESC_KEY)
		exit(0);
	ft_render(mlx);
	return (0);
}
