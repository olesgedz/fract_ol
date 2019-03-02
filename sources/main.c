/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:14:14 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/02 17:45:16 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "mlxlib.h"
#include "fractol.h"
#include "mlx.h"

int		main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc != 2)
		return (ft_usage());
	if ((mlx = ft_init("Fract_ol - ", argv[1])) == NULL)
		return (ft_error("error: mlx couldn't init"));
	ft_render(mlx);
	ft_mlx_hooks(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
