/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:24:27 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/16 21:06:44 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>
static void		ft_press_move(t_mlx *mlx)
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
		mlx->cam->scale  *= 1.1;
	if (mlx->keyboard->keys[M_KEY] == TRUE)
		mlx->cam->z -= 0.1;
	if (mlx->keyboard->keys[L_AR_KEY] == TRUE)
		mlx->cam->z += 0.1;
	if (mlx->keyboard->keys[I_KEY] == TRUE)
		mlx->n++;
	if (mlx->keyboard->keys[J_KEY] == TRUE)
		mlx->cam->y -= 0.1;
	if (mlx->keyboard->keys[K_KEY] == TRUE)
		mlx->n--;
	if (mlx->keyboard->keys[L_KEY] == TRUE)
		mlx->cam->y += 0.1;
}

int				ft_handle_keys_press(int key, t_mlx *mlx)
{
	mlx->keyboard->keys[key] = TRUE;
	ft_press_move(mlx);
	if (key == B_KEY)
	{
		mlx->ncolor += 1;
		if (mlx->ncolor > 4)
			mlx->ncolor = 0;
	}
	printf("key:%d\n", key);
	if (key == F_KEY)
	{
		mlx->nfractal += 1;
		if (mlx->nfractal > 2)
			mlx->nfractal = 0;
	}
	if (key == C_KEY)
		mlx->c =  (mlx->c == 0 ? 1 : 0);
	if (key == M_KEY)
		mlx->smooth = (mlx->smooth == 0 ? 1 : 0);
	if (key == ESC_KEY)
		exit(0);
	ft_render(mlx);
	return (0);
}

int				ft_handle_keys_release(int key, t_mlx *mlx)
{
	mlx->keyboard->keys[key] = FALSE;
	ft_render(mlx);
	return (0);
}

int			expose_hook(t_mlx *e)
{
	ft_render(e);
	return (0);
}

int			mouse_hook(int button, int x, int y, t_mlx *mlx)
{

	if (button == SCROLL_UP)
	{
		mlx->cam->scale *= 1.1;
		mlx->cam->offsetx += (x - FRAC_W / 2)/ mlx->cam->scale / 2.51;
		mlx->cam->offsety -= (y - FRAC_H / 2) / mlx->cam->scale/ 2.51;
	}
	else if (button == SCROLL_DOWN &&  mlx->cam->scale > 0.1)
		 mlx->cam->scale /= 1.1;
	if (button == MOUSE_L_KEY)
		mlx->mouse->isdown = TRUE;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		ft_render(mlx);
	return (0);
}


int				ft_mlx_hooks(t_mlx *mlx)
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
