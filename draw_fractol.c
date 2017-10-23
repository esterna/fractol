/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 17:23:21 by esterna           #+#    #+#             */
/*   Updated: 2017/10/22 17:44:23 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				reset_image(t_frame *frame)
{
	int		bpp;
	int		size_line;
	int		endian;

	frame->redraw = 0;
	mlx_destroy_image(frame->mlx, frame->image);
	mlx_clear_window(frame->mlx, frame->window);
	frame->image = (int *)mlx_new_image(frame->mlx, WIN_X, WIN_Y);
	frame->data = (int *)mlx_get_data_addr(frame->image,
								&bpp, &size_line, &endian);
}

static int			*color_gradient(void)
{
	int			*mapping;

	mapping = (int *)malloc(sizeof(int) * 16);
	mapping[0] = 0x421e0f;
	mapping[1] = 0x19071a;
	mapping[2] = 0x09012f;
	mapping[3] = 0x040449;
	mapping[4] = 0x000764;
	mapping[5] = 0x0c2c8a;
	mapping[6] = 0x1852b1;
	mapping[7] = 0x397dd1;
	mapping[8] = 0x86b5e5;
	mapping[9] = 0xd3ecf8;
	mapping[10] = 0xf1e9bf;
	mapping[11] = 0xf8c95f;
	mapping[12] = 0xffaa00;
	mapping[13] = 0xcc8000;
	mapping[14] = 0x995700;
	mapping[15] = 0x6a3403;
	return (mapping);
}

void				get_color(t_frame *frame, int x, int y, int i)
{
	int		n;
	int		*colors;

	if (i == frame->max_iter)
		return ;
	if (frame->fractol == 4)
	{
		frame->data[x + (y * WIN_X)] = 0x081F85 + (i * frame->color_inc);
		return ;
	}
	n = i % 16;
	colors = color_gradient();
	frame->data[x + (y * WIN_X)] = colors[n];
	free(colors);
}

void				(*g_frac[6])(t_frame *frame, int y1, int y2) =
{
	[0] = mandelbrot,
	[1] = julia,
	[2] = newton,
	[3] = fatou,
	[4] = ikeda,
	[5] = rabbit
};

static void			*partition_window(void *fr_tmp)
{
	t_frame		*frame;
	int			i;

	frame = (t_frame *)fr_tmp;
	i = -1;
	while (++i < NTHREAD)
	{
		if (pthread_equal(pthread_self(), frame->threads[i]))
		{
			g_frac[frame->fractol](frame, i * (WIN_Y / NTHREAD),
					(i + 1) * (WIN_Y / NTHREAD));
		}
	}
	return (NULL);
}

int					draw_fractol(t_frame *frame)
{
	int		i;

	if (frame->redraw == 0)
		return (0);
	reset_image(frame);
	i = -1;
	while (++i < NTHREAD)
	{
		frame->t_curr = i;
		pthread_create(&frame->threads[i], NULL, partition_window, frame);
	}
	i = -1;
	while (++i < NTHREAD)
		pthread_join(frame->threads[i], NULL);
	mlx_put_image_to_window(frame->mlx, frame->window, frame->image, 0, 0);
	return (0);
}
