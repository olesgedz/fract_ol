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

static int			ft_draw_menu(t_mlx *mlx)
{
	int		y;
	char *s;
	y = 0;
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y, 0xFFFFFFF, "How to Use");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, "UO to zoom");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, "WASD to shift");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, "IJKL to rotate or ");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 30, y += 25, 0xFFFFFFF, "press lmb and use mouse");
	mlx_string_put(mlx->mlx, mlx->window,
		 FRAC_H + 10, y += 25, 0xFFFFFFF, "M< to rotate on Z axis");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, "B to change color");
	mlx_string_put(mlx->mlx, mlx->window,
		FRAC_H + 10, y += 25, 0xFFFFFFF, ft_strjoin("Number of iterations: ", s = ft_itoa(mlx->n)));
	ft_strdel(&s);
	return (0);
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


t_pixel		julia(t_mlx *mlx, int x, int y)
{
	double	za;
	double	zb;
	double	temp;
	int		i;
	t_complex c;
	za = ((4 * (float)x / FRAC_W - 2) / mlx->cam->scale) + ((mlx->cam->offsetx / FRAC_W));
	zb = ((-4 * (float)y / FRAC_H + 2) / mlx->cam->scale) + ((mlx->cam->offsety / FRAC_H));
	i = 0;
	while (za * za + zb * zb <= 4 && i < mlx->n)
	{
		temp = za;
		za = za * za - zb * zb + mlx->ca;
		zb = 2 * temp * zb + mlx->cb;
		i++;
	}
	c.r = za;
	c.i = zb;
	return ((t_pixel){.c = c, .i = i});
}

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
	}
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
		k = 0;
		while (k++ < WIN_WIDTH)
			*(int *)(image->ptr + ((k + j * WIN_WIDTH) * image->bpp)) =
			k < FRAC_W ? 0x222222 : 0x1E1E1E;
		j++;
	}
}

void	draw_fractal(t_mlx *mlx, t_pixel (*f)(t_mlx *, int, int))
{
	int		x;
	int		y;
	double		i;
	t_pixel temp;
	y = 0;
	while (y < FRAC_H)
	{
		x = 0;
		while (x < FRAC_W)
		{
			if ((*(mlx->data + y * WIN_WIDTH + x)).i != mlx->n)
				ft_image_set_pixel(mlx->image, x, y, get_color(*(mlx->data + y * WIN_WIDTH + x), mlx));
			x++;
		}
		y++;
	}
}

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
ft_draw_background(mlx);
draw_fractal(mlx, julia);

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
	 ft_draw_menu(mlx);
	mlx_destroy_image(mlx->mlx, mlx->image->image);
}
