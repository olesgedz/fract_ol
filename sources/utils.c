/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:18:29 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/17 20:12:18 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "fractol.h"

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

t_map				*get_map(int width, int height)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = width;
	map->height = height;
	map->depth_min = 0;
	map->depth_max = 0;
	map->vectors = ft_memalloc(sizeof(t_vector *) * width * height);
	if (map->vectors == NULL)
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	return (map);
}

t_fractal	*ft_get_fractals(t_mlx *mlx)
{
	static t_fractal fractals[3];

	//fractals = ft_memalloc(sizeof(t_fractal) * 3);
	fractals[0] = (t_fractal){"Julia", julia};
	fractals[1] = (t_fractal){"Mandelbrot", mandelbrot};
	return (fractals);
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
	//mlx->pixel = ft_memalloc(sizeof(t_pixel));
	//mlx->color = ft_colorHextoRgb(mlx->colors[mlx->ncolor]);
	mlx->smooth = 1;
	mlx->clock_prg = clock();
	mlx->cam->offsetx = 0;//(WIN_WIDTH - MENU_WIDTH) / 2;
	mlx->cam->offsety = 0;//WIN_HEIGHT / 2;
	mlx->fractal = ft_get_fractals(mlx);
	mlx->nfractal = 0;
	mlx->fractal[mlx->nfractal].ca = 0;
	mlx->fractal[mlx->nfractal].cb = 0;
	return (mlx);
}

t_vector			*ft_get_vector(int x, int y, int z)
{
	t_vector	*v;

	v = ft_memalloc(sizeof(t_vector));
	if (v == NULL)
		return (NULL);
	v->x = (double)x;
	v->y = (double)y;
	v->z = (double)z;
	v->color = 0xFFFFFF;
	return (v);
}
