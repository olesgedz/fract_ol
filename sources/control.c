/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:24:27 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/11 04:02:54 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"





static void		ft_press_move(t_mlx *mlx)
{
	if (mlx->keyboard->keys[D_KEY] == TRUE)
		mlx->cam->offsetx -= 50 / mlx->cam->scale;
	if (mlx->keyboard->keys[A_KEY] == TRUE)
		mlx->cam->offsetx += 50 / mlx->cam->scale;
	if (mlx->keyboard->keys[S_KEY] == TRUE)
		mlx->cam->offsety += 50 / mlx->cam->scale;
	if (mlx->keyboard->keys[W_KEY] == TRUE)
		mlx->cam->offsety -= 50/mlx->cam->scale;
	if (mlx->keyboard->keys[U_KEY] == TRUE)
		mlx->cam->scale /= 1.1;
	if (mlx->keyboard->keys[O_KEY] == TRUE)
		mlx->cam->scale  *= 1.1;
	if (mlx->keyboard->keys[M_KEY] == TRUE)
		mlx->cam->z -= 0.1;
	if (mlx->keyboard->keys[L_AR_KEY] == TRUE)
		mlx->cam->z += 0.1;
	if (mlx->keyboard->keys[I_KEY] == TRUE)
		mlx->cam->x += 0.1;
	if (mlx->keyboard->keys[J_KEY] == TRUE)
		mlx->cam->y -= 0.1;
	if (mlx->keyboard->keys[K_KEY] == TRUE)
		mlx->cam->x -= 0.1;
	if (mlx->keyboard->keys[L_KEY] == TRUE)
		mlx->cam->y += 0.1;
}

int				ft_handle_keys_press(int key, t_mlx *mlx)
{
	mlx->keyboard->keys[key] = TRUE;
	ft_press_move(mlx);
	if (key == B_KEY)
	{
		mlx->map->ncolor += 1;
		if (mlx->map->ncolor > 5)
			mlx->map->ncolor = 0;
		ft_change_color(mlx->map);
	}
	if (key == KEY_C)
	{
		mlx->c =  0;
	}
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

int			mouse_hook(int button, int x, int y, t_mlx *e)
{
	x -= WIN_WIDTH / 2;
	y -= WIN_HEIGHT / 2;
	if (button == SCROLL_UP)
	{
		e->cam->scale *= 1.1;
		e->cam->offsetx += x /e->cam->scale / 3;
		e->cam->offsety -= y / e->cam->scale/ 3;
	}
	else if (button == SCROLL_DOWN &&  e->cam->scale > 0.1)
		 e->cam->scale /= 1.1;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		ft_render(e);
	return (0);
}


int				ft_mlx_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 0, ft_handle_keys_press, (void *)mlx);
	mlx_expose_hook(mlx->window, expose_hook, mlx);
	mlx_hook(mlx->window, 3, 0, ft_handle_keys_release, (void *)mlx);
//	mlx_mouse_hook(mlx->window, ft_mouse_press, (void *)mlx);
	//mlx_hook(mlx->window, 5, 0, ft_mouse_release, (void *)mlx);
	mlx_hook(mlx->window, 4, (1L << 2), mouse_hook, (void *)mlx);
	mlx_hook(mlx->window, 6, 0, ft_mouse_move, (void *)mlx);
	mlx_hook(mlx->window, 17, 0, ft_error, (void *)0);
	return (0);
}
