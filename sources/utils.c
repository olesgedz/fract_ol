/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:18:29 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/12 18:25:43 by jblack-b         ###   ########.fr       */
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

static void			ft_init_colors(t_mlx *mlx)
{
	mlx->colors = ft_memalloc(sizeof(double) * 10);
	mlx->colors[0] = 0xFF0000;
	mlx->colors[1] = COLOR_DISCO;
	mlx->colors[2] = COLOR_BRICK_RED;
	mlx->colors[3] = COLOR_FLAMINGO;
	mlx->colors[4] = COLOR_JAFFA;
	mlx->colors[5] = COLOR_SAFFRON;
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
	ft_init_colors(mlx);
	mlx->cam->x = -M_PI / 6;
	mlx->cam->y = -M_PI / 6;
	mlx->cam->z = 0;
	mlx->cam->scale = 1;
	mlx->ca = 0;
	mlx->cb = 0;
	mlx->c = 1;
	mlx->n = 100;
	mlx->color = ft_colorHextoRgb(mlx->colors[mlx->ncolor]);
	mlx->clock_prg = clock();
	mlx->cam->offsetx = 0;//(WIN_WIDTH - MENU_WIDTH) / 2;
	mlx->cam->offsety = 0;//WIN_HEIGHT / 2;
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
