/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:24:27 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/01 21:52:02 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlib.h"
#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>

void				ft_press_move(t_mlx *mlx)
{
	if (mlx->keyboard->keys[D_KEY] == TRUE)
		mlx->cam->offsetx += 20.0 / mlx->cam->scale;
	if (mlx->keyboard->keys[A_KEY] == TRUE)
		mlx->cam->offsetx -= 20.0 / mlx->cam->scale;
	if (mlx->keyboard->keys[S_KEY] == TRUE)
		mlx->cam->offsety -= 20 / mlx->cam->scale;
	if (mlx->keyboard->keys[W_KEY] == TRUE)
		mlx->cam->offsety += 20 / mlx->cam->scale;
	if (mlx->keyboard->keys[U_KEY] == TRUE)
		mlx->cam->scale /= 1.1;
	if (mlx->keyboard->keys[O_KEY] == TRUE)
		ft_zoom_to_mouse(mlx);
	if (mlx->keyboard->keys[M_KEY] == TRUE)
		mlx->cam->z -= 0.1;
	if (mlx->keyboard->keys[L_AR_KEY] == TRUE)
		mlx->cam->z += 0.1;
	if (mlx->keyboard->keys[I_KEY] == TRUE)
		mlx->n += 2;
	if (mlx->keyboard->keys[J_KEY] == TRUE)
		mlx->cam->y -= 0.1;
	if (mlx->keyboard->keys[K_KEY] == TRUE)
		mlx->n--;
	if (mlx->keyboard->keys[L_KEY] == TRUE)
		mlx->cam->y += 0.1;
}

int					ft_handle_keys_release(int key, t_mlx *mlx)
{
	mlx->keyboard->keys[key] = FALSE;
	ft_render(mlx);
	return (0);
}

int					expose_hook(t_mlx *e)
{
	ft_render(e);
	return (0);
}

int					mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (button == SCROLL_UP)
		ft_zoom_to_mouse(mlx);
	else if (button == SCROLL_DOWN && mlx->cam->scale > 0.1)
		mlx->cam->scale /= 1.1;
	if (button == MOUSE_L_KEY)
		ft_handle_buttons(mlx);
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		ft_render(mlx);
	return (0);
}

int					ft_mlx_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 0, ft_handle_keys_press, (void *)mlx);
	mlx_expose_hook(mlx->window, expose_hook, mlx);
	mlx_hook(mlx->window, 3, 0, ft_handle_keys_release, (void *)mlx);
	mlx_hook(mlx->window, 4, (1L << 2), mouse_hook, (void *)mlx);
	mlx_hook(mlx->window, 5, 0, ft_mouse_release, (void *)mlx);
	mlx_hook(mlx->window, 6, 0, ft_mouse_move, (void *)mlx);
	mlx_hook(mlx->window, 17, 0, ft_error, (void *)0);
	return (0);
}
