/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:27:18 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/17 19:58:29 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <pthread.h>
#include <stdio.h>

static int			ft_draw_menu(t_mlx *mlx)
{
	int		y;
	char *s;
	y = 0;
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y, 0xFFFFFFF, "How to Use");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, "UO to zoom");
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
		FRAC_H + 10, y += 25, 0xFFFFFFF, ft_strjoin("Number of iterations: ", s = ft_itoa(mlx->n)));
	ft_strdel(&s);
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, ft_strjoin("Zoom: ", s = ft_itoa((int)mlx->cam->scale)));
	ft_strdel(&s);
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, ft_strjoin("Fractal is: ", mlx->fractal[mlx->nfractal].name));
	return (0);
}

t_pixel	mandelbrot(t_mlx *e, int x, int y)
{
	int		i;
	double	za;
	double	zb;
	double	tmp;
	t_complex c;
	e->fractal[e->nfractal].ca = 1.5 * (x - FRAC_W / 2) / (0.5 * e->cam->scale * FRAC_W)
		+ (e->cam->offsetx / FRAC_W / 1.37) - 0.5;
	e->fractal[e->nfractal].cb = (y - FRAC_H / 2) / (0.5 * e->cam->scale * FRAC_H)
		- (e->cam->offsetx / FRAC_H / 1.92);
	za = 0;
	zb = 0;
	i = 0;
	while (za * za + zb * zb <= 4 && i < e->n)
	{
		tmp = za;
		za = tmp * tmp - zb * zb + e->fractal[e->nfractal].ca;
		zb = 2 * tmp * zb + e->fractal[e->nfractal].cb;
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}

t_pixel				randomf(t_mlx *e, int x, int y)
{
	double	za;
	double	zb;
	double	temp;
	int		i;
	t_complex c;
	za = ((4 * (float)x / FRAC_W - 2) / e->cam->scale) + ((e->cam->offsetx / FRAC_W));
	zb = ((-4 * (float)y / FRAC_W + 2) / e->cam->scale) + ((e->cam->offsety / FRAC_W));
	i = 0;
	while (za * za + zb * zb <= 4 && i < e->n)
	{
		temp = za;
		za = za * za - zb * zb + e->fractal[e->nfractal].ca;
		zb = sin(2 * temp * zb + e->fractal[e->nfractal].cb);
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}


t_pixel		burningship(t_mlx *e, int x, int y)
{
	int		i;
	double	za;
	double	zb;
	double	tmp;
	t_complex c;
	e->fractal[e->nfractal].ca = 1.5 * (x - FRAC_W / 2) / (0.5 * e->cam->scale * FRAC_W)
		+ (e->cam->offsetx / FRAC_W / 1.30) - 0.5;
	e->fractal[e->nfractal].cb = (y - FRAC_H / 2) / (0.5 * e->cam->scale * FRAC_H)
		- (e->cam->offsety / FRAC_H / 1.97);
	za = 0;
	zb = 0;
	i = 0;
	while (za * za + zb * zb <= 4 && i < e->n)
	{
		tmp = za;
		za = fabs(tmp * tmp) - zb * zb + e->fractal[e->nfractal].ca;
		zb = 2 * fabs(tmp * zb) + e->fractal[e->nfractal].cb;
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}

t_pixel		julia(t_mlx *mlx, int x, int y)
{
	double	za;
	double	zb;
	double	temp;
	int		i;
	t_complex c;
	za = ((4 * (float)x / FRAC_W - 2) / mlx->cam->scale) + ((mlx->cam->offsetx / FRAC_W));
	zb = ((-4 * (float)y / FRAC_H + 2) / mlx->cam->scale) + ((mlx->cam->offsety / FRAC_H));
	i = 0;
	while (za * za + zb * zb <= 4 && i < mlx->n)
	{
		temp = za;
		za = za * za - zb * zb + mlx->fractal[mlx->nfractal].ca;
		zb = 2 * temp * zb + mlx->fractal[mlx->nfractal].cb;
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}

void	put_pixel(t_image *e, int x, int y, int coloration)
{
	int		r;
	int		g;
	int		b;

	e->stride = 2400;
	e->bpp = 32;
	r = (coloration & 0xFF0000) >> 16;
	g = (coloration & 0xFF00) >> 8;
	b = (coloration & 0xFF);
	if (y >= 0 && x >= 0 && y < WIN_HEIGHT && x < WIN_WIDTH)
	{
		 e->ptr[(y * e->stride) + ((e->bpp / 8) * x) + 2] = r;
		 e->ptr[(y * e->stride) + ((e->bpp / 8) * x) + 1] = g;
		 e->ptr[(y * e->stride) + ((e->bpp / 8) * x)] = b;
	}
}


static void			ft_draw_background(t_mlx *mlx)
{
	t_image *image;
	int		j;
	int		k;

	ft_clear_image(mlx->image);
	image = mlx->image;
	j = 0;
	while (j < WIN_HEIGHT)
	{
		k = 0;
		while (k++ < WIN_WIDTH)
			*(int *)(image->ptr + ((k + j * WIN_WIDTH) * image->bpp)) =
			k < FRAC_W ? 0x222222 : 0x1E1E1E;
		j++;
	}
}

void	draw_fractal(t_mlx *mlx)
{
	int		x;
	int		y;
	double		i;
	t_pixel temp;
	y = 0;
	while (y < FRAC_H)
	{
		x = 0;
		while (x < FRAC_W)
		{
			if ((*(mlx->data + y * WIN_WIDTH + x)).i != mlx->n)
				ft_image_set_pixel(mlx->image, x, y, get_color(*(mlx->data + y * WIN_WIDTH + x), mlx));
			x++;
		}
		y++;
	}
}

void		*render_thread(void *m)
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
			*(t->mlx->data + y * WIN_WIDTH + x)  = t->mlx->fractal[t->mlx->nfractal].pixel(t->mlx, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}


void				ft_render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector	v;
	t_map		*map;
	int			i;
	t_render	*r;
	map = mlx->map;
	mlx->image = ft_new_image(mlx);
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
	ft_draw_background(mlx);
	draw_fractal(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	ft_draw_menu(mlx);
	mlx_destroy_image(mlx->mlx, mlx->image->image);
}
