/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 17:14:04 by esterna           #+#    #+#             */
/*   Updated: 2017/10/22 18:26:17 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				movement_control(int key, t_frame *frame)
{
	if (key == 125)
	{
		frame->y_min += 0.02 * frame->zoom;
		frame->y_max += 0.02 * frame->zoom;
	}
	if (key == 126)
	{
		frame->y_min -= 0.02 * frame->zoom;
		frame->y_max -= 0.02 * frame->zoom;
	}
	if (key == 123)
	{
		frame->x_min -= 0.02 * frame->zoom;
		frame->x_max -= 0.02 * frame->zoom;
	}
	if (key == 124)
	{
		frame->x_min += 0.02 * frame->zoom;
		frame->x_max += 0.02 * frame->zoom;
	}
}

int					key_controls(int key, t_frame *frame)
{
	(key == 53) ? exit(0) : 0;
	movement_control(key, frame);
	(key == 69 || key == 24) ? frame->max_iter += 20 : 0.0;
	((key == 78 || key == 27) && frame->max_iter > 0)
							? frame->max_iter -= 20 : 0.0;
	(key == 32) ? frame->u += 0.01 : 0.0;
	(key == 38 && frame->u > 0.0) ? frame->u -= 0.01 : 0.0;
	if (key == 17)
		frame->toggle = (frame->toggle == 1 ? 0 : 1);
	frame->redraw = 1;
	return (0);
}

int					mouse_move(int x, int y, t_frame *frame)
{
	if (frame->fractol == 0 || frame->fractol == 4 || frame->toggle == 1)
		return (0);
	frame->redraw = 1;
	if (0 <= x && x <= WIN_X && 0 <= y && y <= WIN_Y)
	{
		frame->cr = (double)x / (WIN_X /
					(frame->x_max - frame->x_min)) + frame->x_min;
		frame->ci = (double)y / (WIN_Y /
					(frame->y_max - frame->y_min)) + frame->y_min;
	}
	return (0);
}

double				interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int					mouse_key(int button, int x, int y, t_frame *frame)
{
	double		dx;
	double		dy;
	double		interpolation;

	dx = (double)x / (WIN_X / (frame->x_max - frame->x_min)) + frame->x_min;
	dy = (double)y / (WIN_Y / (frame->y_max - frame->y_min)) + frame->y_min;
	frame->redraw = 1;
	if (button == 4 || button == 5)
	{
		frame->zoom = 1.0;
		(button == 4) ? frame->zoom += 0.1 : 0.0;
		(button == 5) ? frame->zoom -= 0.1 : 0.0;
		interpolation = 1.0 / frame->zoom;
		frame->x_min = interpolate(dx, frame->x_min, interpolation);
		frame->y_min = interpolate(dy, frame->y_min, interpolation);
		frame->x_max = interpolate(dx, frame->x_max, interpolation);
		frame->y_max = interpolate(dy, frame->y_max, interpolation);
	}
	return (0);
}
