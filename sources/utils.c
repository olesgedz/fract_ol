/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:18:29 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/02 18:12:52 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "mlxlib.h"
#include "fractol.h"
#include <stdlib.h>

t_palette						*get_palettes(void)
{
	static t_palette	array[6];

	array[0] =
		(t_palette){2, 0, {0xFF6666, 0xFFFF00}};
	array[1] =
		(t_palette){5, 0, {0x7F1637, 0x047878, 0xFFB733, 0xF57336, 0xC22121}};
	array[2] =
		(t_palette){5, 0, {0x0D1C33, 0x17373C, 0x2B6832, 0x4F9300, 0xA1D700}};
	array[3] =
		(t_palette){5, 0, {0x002F2F, 0x046380, 0xEFECCA, 0xA7A37E, 0xE6E2AF}};
	array[4] =
		(t_palette){7, 10, {0xFF0000, 0xFFFF00, 0x00FF00, 0x00FFFF,
			0x0000FF, 0xFF00FF, 0xFF0000}};
	array[5] = (t_palette){0, 0, {0}};
	return (array);
}

static t_fractal				*ft_get_fractals(void)
{
	static t_fractal fractals[FRACTAL_N];

	fractals[0] = (t_fractal){"Julia", julia, 0, 0};
	fractals[1] = (t_fractal){"Mandelbrot", mandelbrot, 0, 0};
	fractals[2] = (t_fractal){"Burningship", burningship, 0, 0};
	fractals[3] = (t_fractal){"Random#1", randomf, 0, 0};
	fractals[4] = (t_fractal){"Sierpinski Carpet", carpet, 0, 0};
	fractals[5] = (t_fractal){"Fractal Tree", NULL, 0, 0};
	return (fractals);
}

static void						ft_init_const(t_mlx *mlx)
{
	mlx->cam->x = -M_PI / 6;
	mlx->cam->y = -M_PI / 6;
	mlx->cam->z = 0;
	mlx->cam->scale = 1;
	mlx->data->c = 1;
	mlx->data->n = 32;
	mlx->buttons = ft_get_buttons();
	mlx->data->smooth = 1;
	mlx->cam->offsetx = 0;
	mlx->cam->offsety = 0;
	mlx->data->fractal = ft_get_fractals();
	mlx->data->fractal[mlx->data->nfractal].ca = 0;
	mlx->data->fractal[mlx->data->nfractal].cb = 0;
	mlx->data->size_tree = 1;
	mlx->data->size_tree2 = 1;
}

int								ft_choose_frac(char *argv)
{
	if (!ft_strcmp(argv, "-J"))
		return (0);
	else if (!ft_strcmp(argv, "-M"))
		return (1);
	else if (!ft_strcmp(argv, "-B"))
		return (2);
	else if (!ft_strcmp(argv, "-R"))
		return (3);
	else if (!ft_strcmp(argv, "-S"))
		return (4);
	else if (!ft_strcmp(argv, "-T"))
		return (5);
	ft_usage();
	return (0);
}

t_mlx							*ft_init(char *title, char *argv)
{
	t_mlx	*mlx;
	int		n;

	n = ft_choose_frac(argv);
	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx = mlx_init()) == NULL ||
		(mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH,
			WIN_HEIGHT, title)) == NULL ||
		(mlx->cam = ft_memalloc(sizeof(t_cam))) == NULL ||
		(mlx->mouse = ft_memalloc(sizeof(t_mouse))) == NULL ||
		(mlx->keyboard = ft_memalloc(sizeof(t_keyboard))) == NULL ||
		(mlx->keyboard->keys = ft_memalloc(sizeof(int) * 200)) == NULL ||
		(mlx->image = ft_new_image(mlx)) == NULL)
		return (ft_mlxdel(mlx));
	mlx->data = ft_memalloc(sizeof(t_data));
	mlx->data->nfractal = n;
	ft_bzero((char *)mlx->keyboard->keys, 100);
	mlx->palette = get_palettes();
	mlx->clock_prg = clock();
	ft_init_const(mlx);
	return (mlx);
}
