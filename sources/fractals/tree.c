/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:33:49 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/02 17:44:46 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlib.h"
#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

static void				ft_image_set_pixel_tree(t_image *image,
		int x, int y, int color)
{
	if (y >= 0 && x >= 0 && y < FRAC_H && x < FRAC_W)
		*(int *)(image->ptr + ((x + y * WIN_WIDTH) * image->bpp)) = color;
}

static int				ft_put_points_tree(t_mlx *mlx,
		t_line *l, t_point *p1)
{
	double percentage;

	if (l->dx > l->dy)
		percentage = ft_percent(l->start.x, l->end.x, p1->x);
	else
		percentage = ft_percent(l->start.y, l->end.y, p1->y);
	ft_image_set_pixel_tree(mlx->image, (int)p1->x,
	(int)p1->y, ft_get_color(mlx->palette[mlx->ncolor].colors[0],
		mlx->palette[mlx->ncolor].colors[1], percentage));
	l->err2 = l->err;
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}
	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}

static void				ft_plotline_tree(t_mlx *mlx, t_point p1, t_point p2)
{
	t_line	line;

	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	line.start = p1;
	line.end = p2;
	line.dx = (int)ABS((int)p2.x - (int)p1.x);
	line.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	line.dy = (int)ABS((int)p2.y - (int)p1.y);
	line.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
		if (ft_put_points_tree(mlx, &line, &p1))
			break ;
}

void					draw_tree(t_mlx *mlx,
		t_point start, double angle, int iter)
{
	t_point	end;

	if (iter > 0)
	{
		end.x = start.x + (cos(angle) * iter * 6) * mlx->cam->scale;
		end.y = start.y + (sin(angle) * iter * 9) * mlx->cam->scale;
		ft_plotline_tree(mlx, start, end);
		draw_tree(mlx, end, angle - (M_PI\
			/ 8 * mlx->data->size_tree * 2), iter - 1);
		draw_tree(mlx, end, angle + (M_PI\
			/ 8 * mlx->data->size_tree2 * 2), iter - 1);
	}
}
