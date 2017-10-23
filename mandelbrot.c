/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 17:28:19 by esterna           #+#    #+#             */
/*   Updated: 2017/10/22 18:07:43 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int			utility(double draw[], int max_iter)
{
	int		i;

	i = 0;
	while (i < max_iter)
	{
		draw[2] = draw[4];
		draw[3] = draw[5];
		draw[4] = draw[2] * draw[2] - draw[3] * draw[3] + draw[0];
		draw[5] = 2.0 * draw[3] * draw[2] + draw[1];
		if (draw[4] * draw[4] + draw[5] * draw[5] > 4)
			break ;
		i++;
	}
	return (i);
}

void				mandelbrot(t_frame *frame, int y1, int y2)
{
	int			x;
	double		draw[6];

	while (y1 < y2)
	{
		x = 0;
		while (x < WIN_X)
		{
			draw[0] = (double)x / (WIN_X /
					(frame->x_max - frame->x_min)) + frame->x_min;
			draw[1] = (double)y1 / (WIN_Y /
					(frame->y_max - frame->y_min)) + frame->y_min;
			draw[2] = 0;
			draw[3] = 0;
			draw[4] = 0;
			draw[5] = 0;
			get_color(frame, x, y1, utility(draw, frame->max_iter));
			x++;
		}
		y1++;
	}
}
