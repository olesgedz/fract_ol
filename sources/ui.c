/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:39:35 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/28 18:00:03 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlib.h"
#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <pthread.h>

int					ft_draw_menu(t_mlx *mlx)
{
	int		y;
	char	*s;
	char	*a;

	y = 0;
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y, 0xFFFFFFF, "How to Use");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, "UO to scale");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, "WASD to shift");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, "IJKL to rotate or ");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 30, y += 25, 0xFFFFFFF, "press lmb and use mouse");
	mlx_string_put(mlx->mlx, mlx->window,
		 FRAC_H + 10, y += 25, 0xFFFFFFF, "M< to rotate on Z axis");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, "B to change color");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, s = ft_strjoin("Number of iterations: ",  a = ft_itoa(mlx->n)));
	ft_strdel(&s);
	ft_strdel(&a);
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF,  s = ft_strjoin("scale: ", a = ft_itoa((int)mlx->cam->scale)));
	ft_strdel(&s);
	ft_strdel(&a);
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 120, y += 35, 0xFFFFFFF, s = ft_strjoin(ft_strnewch(((18 - ft_strlen(mlx->fractal[mlx->nfractal].name)) / 2), ' '),
		 mlx->fractal[mlx->nfractal].name));
	ft_strdel(&s);
	return (0);
}

void				ft_draw_onebutton(t_mlx *mlx, t_button *button)
{
	int i = 0;
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
	while(i < BUTTONS_N)
	{
		ft_draw_onebutton(mlx, mlx->buttons + i);
		i++;
	}
}
