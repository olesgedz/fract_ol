/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:14:14 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/25 02:23:49 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
 #include "libft.h"
// #include "fractol.h"
#include "mlx.h"
#include "mlxlib.h"

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	if ((mlx = ft_init("Fract_ol - ")) == NULL)
		return (ft_error("error: mlx couldn't init"));
	ft_render(mlx);
	ft_mlx_hooks(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
