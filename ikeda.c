/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ikeda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 00:06:27 by esterna           #+#    #+#             */
/*   Updated: 2017/10/22 18:12:48 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double		theta(double *draw)
{
	return (0.4 - (6.0 / (1.0 + (draw[2] * draw[2]) + (draw[3] * draw[3]))));
}

static int			utility(double draw[], double u, int max_iter)
{
	int		i;
	double	t;

	i = 0;
	while (i < max_iter)
	{
		draw[2] = draw[4];
		draw[3] = draw[5];
		t = theta(draw);
		draw[4] = 1.0 + u *
			(draw[2] * cos(t) - draw[3] * sin(t));
		draw[5] = u * (draw[2] * sin(t) + draw[3] * cos(t));
		if (draw[4] * draw[4] + draw[5] * draw[5] > 2)
			break ;
		i++;
	}
	return (i);
}

void				ikeda(t_frame *frame, int y1, int y2)
{
	int		x;
	double	draw[6];

	while (y1 < y2)
	{
		x = 0;
		while (x < WIN_X)
		{
			draw[4] = (double)x / (WIN_X /
					(frame->x_max - frame->x_min)) + frame->x_min;
			draw[5] = (double)y1 / (WIN_Y /
					(frame->y_max - frame->y_min)) + frame->y_min;
			get_color(frame, x, y1, utility(draw, frame->u, frame->max_iter));
			x++;
		}
		y1++;
	}
}
