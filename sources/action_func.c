/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:35:05 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/26 21:35:35 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
