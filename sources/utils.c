/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:18:29 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/26 21:22:47 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "mlxlib.h"
#include "fractol.h"
#include <stdlib.h>

t_image		*ft_new_image(t_mlx *mlx)
{
	t_image		*img;

	if ((img = ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->image = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT)) == NULL)
		return (ft_del_image(mlx, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
			&img->endian);
	img->bpp /= 8;
	return (img);
}

t_palette	*get_palettes(void)
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


t_fractal	*ft_get_fractals(t_mlx *mlx)
{
	static t_fractal fractals[FRACTAL_N];

	fractals[0] = (t_fractal){"Julia", julia};
	fractals[1] = (t_fractal){"Mandelbrot", mandelbrot};
	fractals[2] = (t_fractal){"Burningship", burningship};
	fractals[3] = (t_fractal){"Random#1", randomf};
	fractals[4] = (t_fractal){"Sierpinski Carpet", carpet};
	fractals[5] = (t_fractal){"Fractal Tree", NULL};
	return (fractals);
}

void	ft_next_fractal(t_mlx *mlx)
{
	mlx->nfractal += 1;
	if (mlx->nfractal > FRACTAL_N - 1)
		mlx->nfractal = 0;
}

void	ft_previous_fractal(t_mlx *mlx)
{
	mlx->nfractal -= 1;
	if (mlx->nfractal < 0)
		mlx->nfractal = FRACTAL_N - 1;
}

void	ft_switch_smoothing(t_mlx *mlx)
{
		mlx->smooth = (mlx->smooth == 0 ? 1 : 0);
}


void	ft_mouse_parameters_switch(t_mlx *mlx)
{
	mlx->c =  (mlx->c == 0 ? 1 : 0);
}

void	ft_switch_color(t_mlx *mlx)
{
	mlx->ncolor += 1;
	if (mlx->ncolor > 4)
		mlx->ncolor = 0;
}


t_figure *ft_get_figures(t_figure *f1, t_figure *f2, t_figure *f3)
{
	t_figure *figures;

	figures = malloc(sizeof(t_figure) * 3);
	figures[0] = *f1;
	figures[1] = *f2;
	figures[2] = *f3;
	return(figures);
}

t_point *ft_get_points(t_point *p1, t_point *p2, t_point *p3, t_point *p4)
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



t_mlx				*ft_init(char *title)
{
	t_mlx	*mlx;

	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx = mlx_init()) == NULL ||
		(mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH,
			WIN_HEIGHT, title)) == NULL ||
		(mlx->cam = ft_memalloc(sizeof(t_cam))) == NULL ||
		(mlx->mouse = ft_memalloc(sizeof(t_mouse))) == NULL ||
		(mlx->keyboard = ft_memalloc(sizeof(t_keyboard))) == NULL ||
		(mlx->keyboard->keys = ft_memalloc(sizeof(int) * 200)) == NULL ||
		(mlx->image = ft_new_image(mlx)) == NULL || (mlx->color = ft_memalloc(sizeof(t_color))) == NULL)
		return (ft_mlxdel(mlx));
	ft_bzero((char *)mlx->keyboard->keys, 100);
	mlx->cam->x = -M_PI / 6;
	mlx->cam->y = -M_PI / 6;
	mlx->cam->z = 0;
	mlx->cam->scale = 1;
	mlx->c = 1;
	mlx->n = 32;
	mlx->palette = get_palettes();
	mlx->data = ft_memalloc(sizeof(t_pixel) * WIN_WIDTH * WIN_HEIGHT);
	mlx->buttons = ft_get_buttons();
	mlx->smooth = 1;
	mlx->clock_prg = clock();
	mlx->cam->offsetx = 0;
	mlx->cam->offsety = 0;
	mlx->fractal = ft_get_fractals(mlx);
	mlx->nfractal = 0;
	mlx->fractal[mlx->nfractal].ca = 0;
	mlx->fractal[mlx->nfractal].cb = 0;
	mlx->size_tree = 1;
	mlx->size_tree2 = 1;
	return (mlx);
}
