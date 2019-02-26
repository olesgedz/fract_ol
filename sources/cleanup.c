/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:38:42 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/26 21:22:49 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include "mlxlib.h"

int			ft_error(char *reason)
{
	ft_putendl(reason);
	exit(-1);
	return (1);
}


t_image		*ft_del_image(t_mlx *mlx, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(mlx->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

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

int			ft_check_line(char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((!ft_isdigit(s[i])) && s[i] != '+' && s[i] != '-'
		&& !ft_is_space(s[i]))
			return (0);
		i++;
	}
	return (1);
}
