/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 22:54:12 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/28 21:34:32 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"

static void				ft_button_is_pressed(t_mlx *mlx, t_button *button)
{
	if (mlx->mouse->isdown &&
		ft_range_search(button, &((t_point){mlx->mouse->x, mlx->mouse->y})))
	{
		button->pressed(mlx);
		ft_render(mlx);
	}
}

void					ft_handle_buttons(t_mlx *mlx)
{
	int i;

	i = 0;
	mlx->mouse->isdown = TRUE;
	while (i < BUTTONS_N)
		ft_button_is_pressed(mlx, &mlx->buttons[i++]);
}

t_figure				*ft_get_figures(t_figure *f1,
		t_figure *f2, t_figure *f3)
{
	t_figure *figures;

	figures = malloc(sizeof(t_figure) * 3);
	figures[0] = *f1;
	figures[1] = *f2;
	figures[2] = *f3;
	return (figures);
}

t_point					*ft_get_points(t_point *p1, t_point *p2,\
		t_point *p3, t_point *p4)
{
	t_point *points;

	points = ft_memalloc(sizeof(points) * 4);
	points[0] = *p1;
	points[1] = *p2;
	points[2] = *p3;
	points[3] = *p4;
	return (points);
}

t_button				*ft_get_buttons(void)
{
	static t_button buttons[BUTTONS_N];

	buttons[0] = *ft_get_button_one();
	buttons[1] = *ft_get_button_two();
	buttons[2] = *ft_get_button_three();
	buttons[3] = *ft_get_button_four();
	buttons[4] = *ft_get_button_five();
	return (buttons);
}
