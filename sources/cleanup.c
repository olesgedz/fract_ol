/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:38:42 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/01 23:15:49 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include "mlxlib.h"

t_mlx		*ft_mlxdel(t_mlx *mlx)
{
	if (mlx->window != NULL)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->cam != NULL)
		ft_memdel((void **)&mlx->cam);
	if (mlx->mouse != NULL)
		ft_memdel((void **)&mlx->mouse);
	if (mlx->image != NULL)
		ft_del_image(mlx, mlx->image);
	ft_memdel((void **)&mlx);
	return (NULL);
}

int		ft_usage(void)
{
	char usage[] = "usage: fractol  -J for Julia\
	\n\t\t-M for Mandelbrot\
	\n\t\t-B for Burningship\
	\n\t\t-R for Random#1\
	\n\t\t-S for Sierpinski Carpet\
	\n\t\t-T for Fractal Tree";
	return (ft_error(usage));
}
