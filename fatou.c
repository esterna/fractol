/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatou.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 23:53:02 by esterna           #+#    #+#             */
/*   Updated: 2017/10/22 18:30:42 by esterna          ###   ########.fr       */
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
		draw[4] = ft_pow(draw[3], 7.0) - 21.0 *
					ft_pow(draw[3], 5.0) * ft_pow(draw[2], 2.0)
					+ 35.0 * ft_pow(draw[3], 3.0) *
					ft_pow(draw[2], 4.0) - 7.0 * draw[3] * ft_pow(draw[2], 6.0)
					+ draw[0];
		draw[5] = 7.0 * ft_pow(draw[3], 6.0) * draw[2] -
					35.0 * ft_pow(draw[3], 4.0) * ft_pow(draw[2], 3.0)
					+ 21.0 * ft_pow(draw[3], 2.0) * ft_pow(draw[2], 5.0) -
					ft_pow(draw[2], 7.0) + draw[1];
		if (draw[4] * draw[4] + draw[5] * draw[5] > 2)
			break ;
		i++;
	}
	return (i);
}

void				fatou(t_frame *frame, int y1, int y2)
{
	int		x;
	double	draw[6];

	draw[0] = frame->cr;
	draw[1] = frame->ci;
	while (y1 < y2)
	{
		x = 0;
		while (x < WIN_X)
		{
			draw[4] = (double)x / (WIN_X /
						(frame->x_max - frame->x_min)) + frame->x_min;
			draw[5] = (double)y1 / (WIN_Y /
						(frame->y_max - frame->y_min)) + frame->y_min;
			get_color(frame, x, y1, utility(draw, frame->max_iter));
			x++;
		}
		y1++;
	}
}
