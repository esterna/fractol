/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 16:24:46 by esterna           #+#    #+#             */
/*   Updated: 2017/10/22 18:31:43 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_macos_10.11/mlx.h"
# include "libft/libft.h"
# include "libftprintf/libftprintf.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>

# define WIN_X				1800
# define WIN_Y				1200
# define NTHREAD			8

typedef struct				s_frame
{
	void		*mlx;
	void		*window;
	int			*image;
	int			*data;
	int			fractol;
	int			toggle;
	double		zoom;
	double		x_max;
	double		y_max;
	double		x_min;
	double		y_min;
	int			redraw;
	int			max_iter;
	long long	color_inc;
	double		u;
	double		cr;
	double		ci;
	pthread_t	threads[NTHREAD];
	int			t_curr;
}							t_frame;

typedef struct				s_draw
{
	double		zor;
	double		zoi;
	double		znr;
	double		zni;
	double		cr;
	double		ci;
}							t_draw;

int							draw_fractol(t_frame *frame);

void						fatou(t_frame *frame, int y1, int y2);

void						fractol_welcome(t_frame *frame);

void						get_color(t_frame *frame, int x, int y, int iter);

void						ikeda(t_frame *frame, int y1, int y2);

void						julia(t_frame *frame, int y1, int y2);

int							key_controls(int key, t_frame *frame);

void						mandelbrot(t_frame *frame, int y1, int y2);

int							mouse_key(int button, int x, int y, t_frame *frame);

int							mouse_move(int x, int y, t_frame *frame);

void						newton(t_frame *frame, int y1, int y2);

void						rabbit(t_frame *frame, int y1, int y2);

void						reset_image(t_frame *frame);

#endif
