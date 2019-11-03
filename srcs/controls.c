/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 02:51:07 by pthan             #+#    #+#             */
/*   Updated: 2019/10/25 02:51:09 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void zoom(int key, int x, int y, t_fractal *fractal)
{
	if (key == MOUSE_SCROLL_UP)
	{
		// A essayer si pb :
		//fractal->x1 = (fractal->x1 + (x / fractal->zoom_x)) - (x / (fractal->zoom_x / 4));
		fractal->x1 = (fractal->x1 + (x / fractal->zoom_x)) - (WIN_WIDTH / (fractal->zoom_x / 4));
		fractal->x2 = (fractal->x1 + (x / fractal->zoom_x)) + (WIN_WIDTH / (fractal->zoom_x / 4));
		fractal->y1 = (fractal->y1 + (y / fractal->zoom_y)) - (WIN_HEIGHT / (fractal->zoom_y / 4));
		fractal->y2 = (fractal->y1 + (y / fractal->zoom_y)) + (WIN_HEIGHT / (fractal->zoom_y / 4));
		fractal->zoom_x = WIN_WIDTH / (fractal->x2 - fractal->x1);
		fractal->zoom_y = WIN_HEIGHT / (fractal->y2 - fractal->y1);
		fractal->i_max *= 1.1;
	}
	if (key == MOUSE_SCROLL_DOWN)
	{
		fractal->x1 = (fractal->x1 + (x / fractal->zoom_x)) - (WIN_WIDTH / (fractal->zoom_x));
		fractal->x2 = (fractal->x1 + (x / fractal->zoom_x)) + (WIN_WIDTH / (fractal->zoom_x));
		fractal->y1 = (fractal->y1 + (y / fractal->zoom_y)) - (WIN_HEIGHT / (fractal->zoom_y));
		fractal->y2 = (fractal->y1 + (y / fractal->zoom_y)) + (WIN_HEIGHT / (fractal->zoom_y));
		fractal->zoom_x = WIN_WIDTH / (fractal->x2 - fractal->x1);
		fractal->zoom_y = WIN_HEIGHT / (fractal->y2 - fractal->y1);
		fractal->i_max *= 0.9;
	}
	draw(fractal);
}

void move(int key, t_fractal *fractal)
{
	if (key == ARROW_LEFT)
		fractal->x1 -= (fractal->x2 - fractal->x1) * 0.1;
	else if (key == ARROW_RIGHT)
		fractal->x2 += (fractal->x2 - fractal->x1) * 0.1;
	else if (key == ARROW_UP)
		fractal->y1 -= (fractal->y2 - fractal->y1) * 0.1;
	else if (key == ARROW_DOWN)
		fractal->y2 += (fractal->y2 - fractal->y1) * 0.1;
	draw(fractal);
}

int key_press(int key, void *param)
{
	t_fractal *fractal;

	fractal = (t_fractal *)param;
	if (key == MAIN_PAD_ESC)
		exit(0);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN)
		move(key, fractal);
	return (0);
}

int mouse_press(int button, int x, int y, void *param)
{
	t_fractal *fractal;

	fractal = (t_fractal *)param;
	if (button == MOUSE_SCROLL_DOWN && fractal->zoom_x > 1)
		zoom(button, x, y, fractal);
	else if (button == MOUSE_SCROLL_UP && fractal->zoom_x < 2000000000)
		zoom(button, x, y, fractal);
	draw(fractal);
	return (0);
}

int mouse_bis(int button, int x, int y, void *param)
{
	t_fractal *fractal;

	fractal = (t_fractal *)param;
	if (fractal->fractal_nb == 2)
	{
		fractal->c_r *= x / fractal->zoom_x;
		fractal->c_i *= y / fractal->zoom_y;
		draw(fractal);
	}
	return (0);
}
