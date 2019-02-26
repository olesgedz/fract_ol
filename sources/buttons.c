/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 22:54:12 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/26 22:58:00 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"

static void ft_button_is_pressed(t_mlx *mlx, t_button *button)
{
	if (mlx->mouse->isdown &&
		ft_range_search(button, &((t_point){mlx->mouse->x, mlx->mouse->y})))
	{
		button->pressed(mlx);
		ft_render(mlx);
	}
}

void	ft_handle_buttons(t_mlx *mlx)
{
	int i;

	i = 0;
	mlx->mouse->isdown = TRUE;
	while (i < BUTTONS_N)
		ft_button_is_pressed(mlx, &mlx->buttons[i++]);
}


static t_figure *ft_get_figures(t_figure *f1, t_figure *f2, t_figure *f3)
{
	t_figure *figures;

	figures = malloc(sizeof(t_figure) * 3);
	figures[0] = *f1;
	figures[1] = *f2;
	figures[2] = *f3;
	return(figures);
}

static t_point *ft_get_points(t_point *p1, t_point *p2, t_point *p3, t_point *p4)
{
	t_point *points;

	points = ft_memalloc(sizeof(points) * 4);
	points[0] = *p1;
	points[1] = *p2;
	points[2] = *p3;
	points[3] = *p4;
	return(points);
}

t_button *ft_get_buttons()
{
	static t_button buttons[BUTTONS_N];
	buttons[0] = (t_button){{750, 227}, 50, 50, ft_previous_fractal,
		ft_get_figures(&((t_figure){ft_get_points(&((t_point){50, 0}),&((t_point){0, 25}), &((t_point){50, 50}), &((t_point){0, 0})), 0xFFFF00, ft_draw_tr}),
					&((t_figure){ft_get_points(&((t_point){50, 10}),&((t_point){10, 25}),&((t_point){50, 40}), &((t_point){0, 0})), 0xFF6666, ft_draw_tr}),
					&((t_figure ){ft_get_points(&((t_point){50, 10}),&((t_point){25, 25}),&((t_point){50, 40}), &((t_point){0, 0})), MENU_BACKGROUND, ft_draw_tr}))};
	buttons[1] = (t_button){{1050, 227}, 50, 50, ft_next_fractal,
		ft_get_figures(&((t_figure){ft_get_points(&((t_point){0, 0}),&((t_point){50, 25}), &((t_point){0, 50}), &((t_point){0, 0})), 0xFFFF00, ft_draw_tr}),
			&((t_figure){ft_get_points(&((t_point){0, 10}),&((t_point){40, 25}),&((t_point){0, 40}), &((t_point){0, 0})), 0xFF6666, ft_draw_tr}),
			&((t_figure ){ft_get_points(&((t_point){0, 10}),&((t_point){25, 25}),&((t_point){0, 40}), &((t_point){0, 0})), MENU_BACKGROUND, ft_draw_tr}))};
	buttons[2] = (t_button){{1050, 327}, 50, 50, ft_switch_color,
		ft_get_figures(&((t_figure){ft_get_points(&((t_point){25, 25}),&((t_point){25, 25}), &((t_point){0, 50}), &((t_point){0, 0})), 0xFFFF00, ft_draw_cr}),
			&((t_figure){ft_get_points(&((t_point){0, 0}),&((t_point){0, 0}),&((t_point){0, 0}), &((t_point){0, 0})), 0xFF6666, NULL}),
			&((t_figure ){ft_get_points(&((t_point){0, 0}),&((t_point){0, 0}),&((t_point){0, 0}), &((t_point){0, 0})), MENU_BACKGROUND, NULL}))};

	return (buttons);
}
