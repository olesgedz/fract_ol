/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:27:18 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/28 16:53:11 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlib.h"
#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <pthread.h>

void				draw_fractal(t_mlx *mlx)
{
	int			x;
	int			y;
	double		i;
	t_pixel		temp;

	y = 0;
	while (y < FRAC_H)
	{
		x = 0;
		while (x < FRAC_W)
		{
			if ((*(mlx->data + y * WIN_WIDTH + x)).i != mlx->n)
				ft_image_set_pixel(mlx->image, x, y,
						get_color(*(mlx->data + y * WIN_WIDTH + x), mlx));
			x++;
		}
		y++;
	}
}

void				*render_thread(void *m)
{
	t_thread	*t;
	int			x;
	int			y;

	t = (t_thread *)m;
	y = WIN_HEIGHT / THREADS * t->id;
	while (y < WIN_HEIGHT / THREADS * (t->id + 1))
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			*(t->mlx->data + y * WIN_WIDTH + x) = t->mlx->fractal\
					[t->mlx->nfractal].pixel(t->mlx, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

void				ft_multi_threading(t_mlx *mlx)
{
	int			i;
	t_render	*r;

	i = 0;
	r = &mlx->render;
	while (i < THREADS)
	{
		r->args[i].id = i;
		r->args[i].mlx = mlx;
		pthread_create(r->threads + i, NULL, render_thread, &(r->args[i]));
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(r->threads[i], NULL);
		i++;
	}
}

void				ft_draw_switch(t_mlx *mlx)
{
	t_point start;

	ft_draw_background(mlx);
	if (mlx->nfractal != 5)
	{
		ft_multi_threading(mlx);
		draw_fractal(mlx);
	}
	else
	{
		start.x = FRAC_W / 2 - (mlx->cam->offsetx * (mlx->cam->scale / 4.1));
		start.y = FRAC_H - 20 + (mlx->cam->offsety * (mlx->cam->scale / 1.2));
		draw_tree(mlx, start, -(M_PI / 2), mlx->n / 5 + 1);
	}
}

void				ft_render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector	v;

	mlx->image = ft_new_image(mlx);
	ft_draw_switch(mlx);
	ft_draw_buttons(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	ft_draw_menu(mlx);
	mlx_destroy_image(mlx->mlx, mlx->image->image);
}
