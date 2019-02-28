/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:24:45 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/28 18:06:41 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"

t_button	*ft_get_button_one(void)
{
	static t_button new;

	new = (t_button){{750, 227}, 50, 50, ft_previous_fractal,
		ft_get_figures(&((t_figure){ft_get_points(&((t_point){50, 0}),
		&((t_point){0, 25}), &((t_point){50, 50}), &((t_point){0, 0})),
		0xFFFF00, ft_draw_tr}),
		&((t_figure){ft_get_points(&((t_point){50, 10}),
		&((t_point){10, 25}), &((t_point){50, 40}), &((t_point){0, 0})),
		0xFF6666, ft_draw_tr}),
		&((t_figure){ft_get_points(&((t_point){50, 10}),
		&((t_point){25, 25}), &((t_point){50, 40}), &((t_point){0, 0})),
		MENU_BACKGROUND, ft_draw_tr}))};
	return (&new);
}

t_button	*ft_get_button_two(void)
{
	static t_button new;

	new = (t_button){{1050, 227}, 50, 50, ft_next_fractal,
		ft_get_figures(&((t_figure){ft_get_points(&((t_point){0, 0}),
	&((t_point){50, 25}), &((t_point){0, 50}), &((t_point){0, 0})),
	0xFFFF00, ft_draw_tr}), &((t_figure){ft_get_points(&((t_point){0, 10}),
	&((t_point){40, 25}), &((t_point){0, 40}),
	&((t_point){0, 0})), 0xFF6666, ft_draw_tr}),
	&((t_figure){ft_get_points(&((t_point){0, 10}), &((t_point){25, 25}),
	&((t_point){0, 40}), &((t_point){0, 0})), MENU_BACKGROUND, ft_draw_tr}))};
	return (&new);
}

t_button	*ft_get_button_three(void)
{
	static t_button new;

	new = (t_button){{1050, 327}, 50, 50, ft_switch_color,
		ft_get_figures(&((t_figure){ft_get_points(&((t_point){25, 25}),
	&((t_point){25, 25}), &((t_point){0, 50}),
	&((t_point){0, 0})), 0xFFFF00, ft_draw_cr}),
	&((t_figure){ft_get_points(&((t_point){0, 0}), &((t_point){0, 0}),
	&((t_point){0, 0}), &((t_point){0, 0})), 0xFF6666, NULL}),
	&((t_figure){ft_get_points(&((t_point){0, 0}), &((t_point){0, 0}),
	&((t_point){0, 0}), &((t_point){0, 0})), MENU_BACKGROUND, NULL}))};
	return (&new);
}
