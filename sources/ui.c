/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:39:35 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/02 17:46:33 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlib.h"
#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <pthread.h>

void				ft_draw_static(t_mlx *mlx, int *y)
{
	*y = 0;
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, *y, 0xFFFFFFF, "How to Use");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, *y += 25, 0xFFFFFFF, "UO to scale");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, *y += 25, 0xFFFFFFF, "WASD to shift");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, *y += 25, 0xFFFFFFF, "Press lmb and use mouse to drag");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, *y += 25, 0xFFFFFFF, "B to change color");
	mlx_string_put(mlx->mlx, mlx->window,
			FRAC_H + 10, *y += 25, 0xFFFFFFF, "I/O to change number\
		of iterations");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, *y += 25, 0xFFFFFFF, "C to freeze frame R - reset");
}

void				ft_draw_menu_2(t_mlx *mlx, int *y)
{
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 150, *y += 100, 0xFFFFFFF, "Change color");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 150, *y += 100, 0xFFFFFFF, "Smoothing");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 150, *y += 100, 0xFFFFFFF, "Reset");
}

int					ft_draw_menu(t_mlx *mlx)
{
	int		y;
	char	*s;
	char	*a;

	ft_draw_static(mlx, &y);
	a = ft_itoa(mlx->data->n);
	mlx_string_put(mlx->mlx, mlx->window, FRAC_H + 10, y += 25,
	0xFFFFFFF, s = ft_strjoin("Number of iterations: ", a));
	ft_strdel(&s);
	ft_strdel(&a);
	a = ft_itoa((int)mlx->cam->scale);
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, s = ft_strjoin("scale: ", a));
	ft_strdel(&s);
	ft_strdel(&a);
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 120, y += 100, 0xFFFFFFF, s = ft_strjoin(ft_strnewch(((18 - \
	ft_strlen(mlx->data->fractal[mlx->data->nfractal].name)) / 2), ' '),
		mlx->data->fractal[mlx->data->nfractal].name));
	ft_strdel(&s);
	ft_draw_menu_2(mlx, &y);
	return (0);
}

void				ft_draw_onebutton(t_mlx *mlx, t_button *button)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (button->figures[i].draw != NULL)
			button->figures[i].draw(mlx, button, button->figures + i);
		i++;
	}
}

void				ft_draw_buttons(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < BUTTONS_N)
	{
		ft_draw_onebutton(mlx, mlx->buttons + i);
		i++;
	}
}
