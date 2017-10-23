/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_welcome.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 02:31:16 by esterna           #+#    #+#             */
/*   Updated: 2017/10/22 17:49:40 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				fractol_welcome(t_frame *frame)
{
	ft_printf("\t\tWelcome to Fractol\n\t---------------------------------\n");
	if (frame->fractol == 0)
		ft_printf("\t\t   {red}Mandelbrot{eoc}\n");
	if (frame->fractol == 1)
		ft_printf("\t\t     {blue}Julia{eoc}\n");
	if (frame->fractol == 2)
		ft_printf("\t\t     {yellow}Newton{eoc}\n");
	if (frame->fractol == 3)
		ft_printf("\t\t      {green}Fatou{eoc}\naka Julia to the 7th power\n");
	if (frame->fractol == 4)
		ft_printf("\t\t   {cyan}Ikeda Map{eoc}\n");
	if (frame->fractol == 5)
		ft_printf("\t\t  {magenta}Douady Rabbit{eoc}\n");
	if (frame->fractol != 0 && frame->fractol != 4)
	{
		ft_printf("Scroll mouse over window to change C constant\n");
		ft_printf("'t' to toggle changing C constant\n");
	}
	if (frame->fractol == 4)
		ft_printf("u/j to increase/decrease u constant (chaos attractor)\n");
	ft_printf("Arrows for movement\n");
	ft_printf("Mouse scroll for zoom in/out\n");
	ft_printf("+/- to increase/decrease Maximum number of Iterations\n");
	ft_printf("ESC to Exit\n");
}
