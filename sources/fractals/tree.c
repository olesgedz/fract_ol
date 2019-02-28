/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:33:49 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/28 17:33:41 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlib.h"
#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

void		draw_tree(t_mlx *mlx, t_point start, double angle, int iter)
{
	t_point	end;

	if (iter > 0)
	{
		end.x = start.x + (cos(angle) * iter * 6) * mlx->cam->scale;
		end.y = start.y + (sin(angle) * iter * 9) * mlx->cam->scale;
		ft_plotline(mlx, start, end);
		draw_tree(mlx, end, angle - (M_PI / 8 * mlx->size_tree * 2), iter - 1);
		draw_tree(mlx, end, angle + (M_PI / 8 * mlx->size_tree2 * 2), iter - 1);
	}
}
