/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:27:18 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/07 21:11:15 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

static int			ft_put_points(t_mlx *mlx,
		t_line *l, t_vector *p1, t_vector *p2)
{
	double percentage;

	if (l->dx > l->dy)
		percentage = ft_percent(l->start.x, l->end.x, p1->x);
	else
		percentage = ft_percent(l->start.y, l->end.y, p1->y);
	ft_image_set_pixel(mlx->image, (int)p1->x,
	(int)p1->y, ft_get_color(p1->color, p2->color, percentage));
	l->err2 = l->err;
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}
	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}

static void			ft_plotline(t_mlx *mlx, t_vector p1, t_vector p2)
{
	t_line	line;

	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	line.start = p1;
	line.end = p2;
	line.dx = (int)ABS((int)p2.x - (int)p1.x);
	line.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	line.dy = (int)ABS((int)p2.y - (int)p1.y);
	line.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
		if (ft_put_points(mlx, &line, &p1, &p2))
			break ;
}

static int			ft_draw_menu(t_mlx *mlx)
{
	int		y;

	y = 0;
	mlx_string_put(mlx->mlx, mlx->window,
		WIN_WIDTH - MENU_WIDTH + 10, y, 0xFFFFFFF, "How to Use");
	mlx_string_put(mlx->mlx, mlx->window,
		WIN_WIDTH - MENU_WIDTH + 10, y += 25, 0xFFFFFFF, "UO to zoom");
	mlx_string_put(mlx->mlx, mlx->window,
		WIN_WIDTH - MENU_WIDTH + 10, y += 25, 0xFFFFFFF, "WASD to shift");
	mlx_string_put(mlx->mlx, mlx->window,
		WIN_WIDTH - MENU_WIDTH + 10, y += 25, 0xFFFFFFF, "IJKL to rotate or ");
	mlx_string_put(mlx->mlx, mlx->window, WIN_WIDTH - MENU_WIDTH + 30,
			y += 25, 0xFFFFFFF, "press lmb and use mouse");
	mlx_string_put(mlx->mlx, mlx->window, WIN_WIDTH - MENU_WIDTH + 10,
			y += 25, 0xFFFFFFF, "M< to rotate on Z axis");
	mlx_string_put(mlx->mlx, mlx->window,
		WIN_WIDTH - MENU_WIDTH + 10, y += 25, 0xFFFFFFF, "B to change color");
	return (0);
}

static void			ft_draw_background(t_mlx *mlx)
{
	t_image *image;
	int		j;
	int		k;

	ft_clear_image(mlx->image);
	image = mlx->image;
	j = 0;
	while (j < WIN_HEIGHT)
	{
		k = -1;
		while (k++ < WIN_WIDTH)
			*(int *)(image->ptr + ((k + j * WIN_WIDTH) * image->bpp)) =
			k < WIN_WIDTH - MENU_WIDTH ? 0x1E1E1E : 0x222222;
		j++;
	}
}

void				ft_render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector	v;
	t_map		*map;

	map = mlx->map;
	x = -1;
	ft_draw_background(mlx);
	//each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
   double cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
   double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
   double zoom = 1, moveX = 0, moveY = 0; //you can change these to zoom and change position
   int maxIterations = 300; //after how much iterations the function should stop

   //pick some values for the constant c, this determines the shape of the Julia Set
   cRe = -0.7;
   cIm = 0.27015;
	 int h = WIN_HEIGHT;
	 int w = WIN_WIDTH;
   //loop through every pixel
   for(int y = 0; y < h; y++)
   for(int x = 0; x < w; x++)
   {
     //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
     newRe = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
     newIm = (y - h / 2) / (0.5 * zoom * h) + moveY;
     //i will represent the number of iterations
     int i;
     //start the iteration process
     for(i = 0; i < maxIterations; i++)
     {
       //remember value of previous iteration
       oldRe = newRe;
       oldIm = newIm;
       //the actual iteration, the real and imaginary part are calculated
       newRe = oldRe * oldRe - oldIm * oldIm + cRe;
       newIm = 2 * oldRe * oldIm + cIm;
       //if the point is outside the circle with radius 2: stop
       if((newRe * newRe + newIm * newIm) > 4) break;
     }
     //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
     //draw the pixel
     ft_image_set_pixel(mlx->image, x, y, 0xC2294E);
   }


	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	ft_draw_menu(mlx);
}
