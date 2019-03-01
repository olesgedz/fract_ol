/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 16:12:18 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/01 21:36:29 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdint.h>
# include <time.h>
# include <string.h>
# include <pthread.h>
# include "mlxlib.h"

void				ft_change_color(t_mlx *mlx, int ncolor);
void				ft_render(t_mlx *mlx);
int					ft_mouse_press(int button, int x, int y, t_mlx *mlx);
int					ft_mouse_release(int button, int x, int y, t_mlx *mlx);
int					ft_mouse_move(int x, int y, t_mlx *mlx);
double				ft_percent(int start, int end, int current);
int					ft_get_color(int c1, int c2, double p);
t_vector			ft_project_vector(t_vector v, t_mlx *mlx);
t_mlx				*ft_init(char *title, char* argv);
int					ft_mlx_hooks(t_mlx *mlx);
t_vector			*ft_get_vector(int x, int y, int z);
t_image				*ft_del_image(t_mlx *mlx, t_image *img);
t_mlx				*ft_mlxdel(t_mlx *mlx);
void				ft_image_set_pixel(t_image *image, int x, int y, int color);
t_pixel				julia(t_mlx *mlx, int x, int y);
t_pixel				carpet(t_mlx *e, int x, int y);
t_pixel				mandelbrot(t_mlx *mlx, int x, int y);
t_pixel				burningship(t_mlx *mlx, int x, int y);
t_pixel				randomf(t_mlx *e, int x, int y);
void				draw_tree(t_mlx *mlx, t_point start,\
		double angle, int iter);
t_image				*ft_new_image(t_mlx *mlx);
int					get_color(t_pixel p, t_mlx *mlx);
void				ft_draw_tr(t_mlx *mlx, t_button *button,\
		t_figure *triangle);
void				ft_image_set_pixel_tree(t_image *image,\
		int x, int y, int color);
void				ft_draw_not(t_mlx *mlx, t_button *button, t_figure *circle);
void				ft_mouse_parameters_switch(t_mlx *mlx);
void				ft_switch_color(t_mlx *mlx);
void				ft_next_fractal(t_mlx *mlx);
void				ft_switch_smoothing(t_mlx *mlx);
void				ft_image_set_pixel_tree(t_image *image,\
		int x, int y, int color);
void				ft_previous_fractal(t_mlx *mlx);
void				ft_handle_buttons(t_mlx *mlx);
t_button			*ft_get_buttons();
void				ft_zoom_to_mouse(t_mlx *mlx);
void				ft_reset_view(t_mlx *mlx);
int					ft_handle_keys_press(int key, t_mlx *mlx);
void				ft_draw_buttons(t_mlx *mlx);
t_button			*ft_get_button_one(void);
int					ft_draw_menu(t_mlx *mlx);
void				ft_press_move(t_mlx *mlx);
t_point				*ft_get_points(t_point *p1,
			t_point *p2, t_point *p3, t_point *p4);
t_figure			*ft_get_figures(t_figure *f1,
		t_figure *f2, t_figure *f3);
void				ft_reset_view(t_mlx *mlx);
int					ft_usage(void);

t_button			*ft_get_button_one(void);
t_button			*ft_get_button_two(void);
t_button			*ft_get_button_three(void);
t_button			*ft_get_button_four(void);
t_button			*ft_get_button_five(void);
#endif
