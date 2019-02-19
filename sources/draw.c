/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:27:18 by jblack-b          #+#    #+#             */
/*   Updated: 2019/02/17 19:58:29 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <pthread.h>
#include <stdio.h>

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
	image = mlx->image;
	j = 0;
	while (j < WIN_HEIGHT)
	{
		k = -1;
		while (k++ < WIN_WIDTH)
			*(int *)(image->ptr + ((k + j * WIN_WIDTH) * image->bpp)) = 0x222222;
		j++;
	}
}

int				ft_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// int		mandelbrot(t_mlx *e, int x, int y)
// {
// 	int		i;
// 	double	za;
// 	double	zb;
// 	double	tmp;
//
// 	e->ca = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * e->cam->scale * WIN_WIDTH)
// 		+ (e->cam->offsetx / WIN_WIDTH / 1.37) - 0.5;
// 	e->cb = (y - WIN_HEIGHT / 2) / (0.5 * e->cam->scale * WIN_HEIGHT)
// 		- (e->cam->x / WIN_HEIGHT / 1.92);
// 	za = 0;
// 	zb = 0;
// 	i = 0;
// 	while (za * za + zb * zb <= 4 && i < e->n)
// 	{
// 		tmp = za;
// 		za = tmp * tmp - zb * zb + e->ca;
// 		zb = 2 * tmp * zb + e->cb;
// 		i++;
// 	}
// 	e->pixel->c.r = za;
// 	e->pixel->c.i = zb;
// 	return (i);
// }


t_pixel		julia(t_mlx *e, int x, int y)
{
	double	za;
	double	zb;
	double	temp;
	int		i;
	t_complex c;
	za = ((4 * (float)x / WIN_WIDTH - 2) / e->cam->scale) + ((e->cam->offsetx / WIN_WIDTH));
	zb = ((-4 * (float)y / WIN_HEIGHT + 2) / e->cam->scale) + ((e->cam->offsety / WIN_HEIGHT));
	i = 0;
	while (za * za + zb * zb <= 4 && i < e->n)
	{
		temp = za;
		za = za * za - zb * zb + e->ca;
		zb = 2 * temp * zb + e->cb;
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}

// t_pixel		julia(t_mlx *mlx, int x, int y)
// {
// 	t_complex	z;
// 	t_complex	c;
// 	t_complex	temp;
// 	int			i;
// 	t_pixel p;
// 	(void)mlx;
// 	i = 0;
// 	while (z.r * z.r + z.i * z.i < (1 << 8) && i < mlx->n)
// 	{
// 		temp.r = z.r * z.r - z.i * z.i + c.r;
// 		temp.i = z.r * z.i * 2 + c.i;
// 		if (z.r == temp.r && z.i == temp.i)
// 		{
// 			i = mlx->n;
// 			break ;
// 		}
// 		z.r = temp.r;
// 		z.i = temp.i;
// 		i++;
// 	}
// 	return ((t_pixel){.c = z, .i = i});
// }

void	put_pixel(t_image *e, int x, int y, int coloration)
{
	int		r;
	int		g;
	int		b;

	e->stride = 2400;
	e->bpp = 32;
	r = (coloration & 0xFF0000) >> 16;
	g = (coloration & 0xFF00) >> 8;
	b = (coloration & 0xFF);
	if (y >= 0 && x >= 0 && y < WIN_HEIGHT && x < WIN_WIDTH)
	{
		 e->ptr[(y * e->stride) + ((e->bpp / 8) * x) + 2] = r;
		 e->ptr[(y * e->stride) + ((e->bpp / 8) * x) + 1] = g;
		 e->ptr[(y * e->stride) + ((e->bpp / 8) * x)] = b;
	//	*(int *)(e->ptr + ((x + y * WIN_WIDTH) * e->bpp)) = coloration;
	}
}


void	draw_fractal(t_mlx *mlx, t_pixel (*f)(t_mlx *, int, int))
{
	int		x;
	int		y;
	double		i;
	t_pixel temp;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{

			 mlx->pixel = (*f)(mlx, x, y);
			if (mlx->pixel.i != mlx->n)
			{
				ft_image_set_pixel(mlx->image, x, y, get_color(*(mlx->data + y * WIN_WIDTH + x), mlx));
				//printf("Hello %ld\n", (mlx->data + y * WIN_WIDTH + x)->i);
			//ft_image_set_pixel(mlx->image, x, y, 0xff0000);
				//printf("%ld\n", mlx->pixel->i);
			}
			x++;
		}
		y++;
	}
}



// t_color *ft_colorHextoRgb(int hex)
// {
// 	t_color *color;
// 	color = ft_memalloc(sizeof(t_color));
// 	color->r = hex >> 16 & 0xFF;
// 	color->g = hex >> 8 & 0xFF;
// 	color->b = hex & 0xFF;
// 	return (color);
// }

void		*render_thread(void *m)
{
	t_thread	*t;
	int			x;
	int			y;
	t = (t_thread *)m;
	y = WIN_HEIGHT / THREADS * t->id;
	while (y < WIN_HEIGHT / THREADS * (t->id + 1))
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			*(t->mlx->data + y * WIN_WIDTH + x)  = julia(t->mlx, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}


void				ft_render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector	v;
	t_map		*map;

	map = mlx->map;

	mlx->image = ft_new_image(mlx);



	int			i;
	t_render	*r;

i = 0;
 r = &mlx->render;
while (i < THREADS)
{
	r->args[i].id = i;
	r->args[i].mlx = mlx;
	 pthread_create(r->threads + i, NULL, render_thread, &(r->args[i]));
	i++;
}
i = 0;
while (i < THREADS)
{
	pthread_join(r->threads[i], NULL);
	i++;
}
mlx->function = julia;
draw_fractal(mlx, julia);
	//ft_draw_background(mlx);
	//ft_clear_image(mlx->image);
	//each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
//    double cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
//    double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
//    double zoom = 1, moveX = 0, moveY = 0; //you can change these to zoom and change position
//    int maxIterations = 100; //after how much iterations the function should stop
// int color = 0;
//    //pick some values for the constant c, this determines the shape of the Julia Set
//    cRe = -0.7;
//    cIm = 0.27015;
// 	 int h = WIN_HEIGHT;
// 	 int w = WIN_WIDTH;
//    //loop through every pixel
//    for(int y = 0; y < h; y++)
//    for(int x = 0; x < w; x++)
//    {
//      //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
//      newRe = 1.5 * (x - w / 2) / (0.5 * mlx->cam->scale * w) + mlx->cam->offsetx/ WIN_WIDTH;
//      newIm = (y - h / 2) / (0.5 * mlx->cam->scale * h) - mlx->cam->offsety/ WIN_HEIGHT;
//      //i will represent the number of iterations
//      int i;
//      //start the iteration process
//      for(i = 0; i < maxIterations; i++)
//      {
//        //remember value of previous iteration
//        oldRe = newRe;
//        oldIm = newIm;
//        //the actual iteration, the real and imaginary part are calculated
//        newRe = oldRe * oldRe - oldIm * oldIm + cRe;
//        newIm = 2 * oldRe * oldIm + cIm;
//        //if the point is outside the circle with radius 2: stop
// 			 color = ((255 - i * 6) << 16) + ((255 - i * 2) << 8)
// 				 + (255 - i * 10);
//        if((newRe * newRe + newIm * newIm) > 4) break;
//      }
//
// 		 if(i != 100)
// 		  ft_image_set_pixel(mlx->image, x, y, color);
// 	 }
     // use color model conversion to get rainbow palette, make brightness black if maxIterations reached
     // draw the pixel
// 	 int h = WIN_HEIGHT;
// 	 int w = WIN_WIDTH;
// 	double pr, pi;           //real and imaginary part of the pixel p
// 	  double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
// 	  //double zoom = 1, moveX = -0.5 - 0.3, moveY = 0; //you can change these to zoom and change position
// 	  int maxIterations = 100;//after how much iterations the function should stop
// int color;
// 	  //loop through every pixel
// 	  for(int y = 0; y < h; y++)
// 	  for(int x = 0; x < w; x++)
// 	  {
// 	    //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
// 	    pr = 1.5 * (x - w / 2) / (0.5 * mlx->cam->scale * w) + 0;
// 	    pi = (y - h / 2) / (0.5 *  mlx->cam->scale * h) + 0;
// 			// printf("%f\n",mlx->cam->scale );
// 	    newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
// 	    //"i" will represent the number of iterations
// 	    int i;
// 	    //start the iteration process
// 	    for(i = 0; i < maxIterations; i++)
// 	    {
// 	      //remember value of previous iteration
// 	      oldRe = newRe;
// 	      oldIm = newIm;
// 	      //the actual iteration, the real and imaginary part are calculated
// 	      newRe = oldRe * oldRe - oldIm * oldIm + pr;
// 	      newIm = 2 * oldRe * oldIm + pi;
// 	      //if the point is outside the circle with radius 2: stop
// 	      if((newRe * newRe + newIm * newIm) > 4) break;
// 	    }
// 			//	t_RGB colorRGB = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));
// 			// int color = ft_rgb(colorRGB.R, 0, colorRGB.B);
// 			// int color = ((255 - i * colorRGB.R) << 16) + ((255 - i *colorRGB.G) << 8)
// 			// 	+ (255 - i * colorRGB.B);
// 			color = ((255 - i * 9) << 16) + ((255 - i * 7) << 8)
// 				+ (255 - i * 12);
// 				if(i != 100)
// 					ft_image_set_pixel(mlx->image, x, y, color);
//
// 			}
// if ((mlx->image->image = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT)))
// {
// 	fill_img(mlx, julia);
// 	//ft_draw_background(mlx);
// 	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
// 	mlx_destroy_image(mlx->mlx, mlx->image->image);
// }



	 //draw_fractal(mlx, julia);
	 mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->image->image);
}
