/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 16:24:20 by esterna           #+#    #+#             */
/*   Updated: 2017/10/22 18:25:27 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				fractol_exit(int i, t_frame *frame)
{
	free(frame);
	if (i == 1)
	{
		ft_printf("{red}usage: ./fractol [name of fractol]{eoc}\n");
		ft_printf("fractals:\tMandelbrot\n\t\tJulia\n\t\t");
		ft_printf("Newton\n\t\tFatou\n\t\tIkeda\n\t\tRabbit\n");
		exit(1);
	}
	mlx_destroy_image(frame->mlx, frame->image);
	mlx_destroy_window(frame->mlx, frame->window);
	exit(0);
}

int					read_params(int argc, char **params, t_frame *frame)
{
	if (argc != 1)
		return (0);
	if (ft_strcmp(params[0], "Mandelbrot") == 0)
		frame->fractol = 0;
	else if (ft_strcmp(params[0], "Julia") == 0)
		frame->fractol = 1;
	else if (ft_strcmp(params[0], "Newton") == 0)
		frame->fractol = 2;
	else if (ft_strcmp(params[0], "Fatou") == 0)
		frame->fractol = 3;
	else if (ft_strcmp(params[0], "Ikeda") == 0)
		frame->fractol = 4;
	else if (ft_strcmp(params[0], "Rabbit") == 0)
		frame->fractol = 5;
	else
		return (0);
	return (1);
}

void				constants_init(t_frame *frame)
{
	frame->x_min = -2.0;
	frame->y_min = -1.0;
	frame->x_max = 1.0;
	frame->y_max = 1.0;
	if (frame->fractol == 5)
	{
		frame->cr = 2.55268;
		frame->ci = -0.959456;
	}
	else
	{
		frame->cr = -0.7;
		frame->ci = 0.27015;
	}
	frame->u = 0.9;
}

void				fractol_init(t_frame *frame)
{
	int		bpp;
	int		size_line;
	int		endian;

	frame->mlx = mlx_init();
	frame->window = mlx_new_window(frame->mlx, WIN_X, WIN_Y, "Fractol");
	frame->image = (int *)mlx_new_image(frame->mlx, WIN_X, WIN_Y);
	frame->data = (int *)mlx_get_data_addr(frame->image,
						&bpp, &size_line, &endian);
	frame->redraw = 1;
	frame->max_iter = 20;
	frame->toggle = 0;
	frame->color_inc = 248359;
	frame->zoom = 1.0;
	constants_init(frame);
}

int					main(int argc, char **argv)
{
	t_frame		*frame;

	frame = (t_frame *)malloc(sizeof(t_frame));
	if (read_params(argc - 1, argv + 1, frame) == 0)
		fractol_exit(1, frame);
	fractol_init(frame);
	fractol_welcome(frame);
	mlx_hook(frame->window, 6, 0, mouse_move, frame);
	mlx_mouse_hook(frame->window, mouse_key, frame);
	mlx_key_hook(frame->window, key_controls, frame);
	mlx_loop_hook(frame->mlx, draw_fractol, frame);
	mlx_loop(frame->mlx);
	return (0);
}
