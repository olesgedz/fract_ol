/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:27:18 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/26 22:25:13 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlib.h"
#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <pthread.h>
#include <stdio.h>


char *ft_strchnew(size_t n, char c)
{
	char *str;

	str = ft_memset(ft_strnew(n), c, n);
	return(str);
}

static int			ft_draw_menu(t_mlx *mlx)
{
	int		y;
	char *s;
	char *a;
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
		FRAC_H + 120, y += 35, 0xFFFFFFF, s = ft_strjoin(ft_strchnew(((18 - ft_strlen(mlx->fractal[mlx->nfractal].name)) / 2), ' '),
		 mlx->fractal[mlx->nfractal].name));
	ft_strdel(&s);
	return (0);
}

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



void ft_multi_threading(t_mlx *mlx)
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

void	ft_draw_switch(t_mlx *mlx)
{
	ft_draw_background(mlx);
	if (mlx->nfractal != 5)
	{
		ft_multi_threading(mlx);
		draw_fractal(mlx);
	}
	else
	{
		t_point start;
		start.x = FRAC_W / 2 - (mlx->cam->offsetx * (mlx->cam->scale / 4.1));
		start.y = FRAC_H- 20 + (mlx->cam->offsety * (mlx->cam->scale  / 1.2));
		draw_tree(mlx, start, -(M_PI / 2), mlx->n / 5 + 1);
	}
}

void	ft_draw_onebutton(t_mlx *mlx, t_button *button)
{
	int i = 0;
	while (i < 3)
	{
		if (button->figures[i].draw != NULL)
			button->figures[i].draw(mlx, button, button->figures + i);
		i++;
	}
}

void ft_draw_buttons(t_mlx *mlx)
{
	int i;

	i = 0;
	while(i < BUTTONS_N)
	{
		ft_draw_onebutton(mlx, mlx->buttons + i);
		i++;
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
