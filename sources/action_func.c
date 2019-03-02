/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:35:05 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/02 17:27:30 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_next_fractal(t_mlx *mlx)
{
	mlx->data->nfractal += 1;
	if (mlx->data->nfractal > FRACTAL_N - 1)
		mlx->data->nfractal = 0;
}

void	ft_previous_fractal(t_mlx *mlx)
{
	mlx->data->nfractal -= 1;
	if (mlx->data->nfractal < 0)
		mlx->data->nfractal = FRACTAL_N - 1;
}

void	ft_switch_smoothing(t_mlx *mlx)
{
	mlx->data->smooth = (mlx->data->smooth == 0 ? 1 : 0);
}

void	ft_mouse_parameters_switch(t_mlx *mlx)
{
	mlx->data->c = (mlx->data->c == 0 ? 1 : 0);
}

void	ft_switch_color(t_mlx *mlx)
{
	mlx->ncolor += 1;
	if (mlx->ncolor > 4)
		mlx->ncolor = 0;
}
