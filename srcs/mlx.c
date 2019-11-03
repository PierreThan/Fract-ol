/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 02:52:37 by pthan             #+#    #+#             */
/*   Updated: 2019/10/25 02:52:38 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key_macos.h"

void ft_display_window(t_mlx *mlx, char *title, int img_width, int img_height)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
								  WIN_WIDTH, WIN_HEIGHT, title);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, img_width, img_height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr,
											 &(mlx->img.bpp), &(mlx->img.size_l), &(mlx->img.endian));
}

int close_fractal(void *param)
{
	(void)param;
	exit(0);
}

void point_to_img(t_fractal *fractal, int x, int y, int color)
{
	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
		fractal->mlx.img.data[x + y * WIN_WIDTH] = color;
}

void setup_controls(t_fractal *fractal)
{
	mlx_hook(fractal->mlx.win_ptr, 2, 0, key_press, fractal);
	mlx_hook(fractal->mlx.win_ptr, 17, 0, close_fractal, fractal);
	mlx_hook(fractal->mlx.win_ptr, 6, 1L < 6, mouse_bis, fractal);
	mlx_hook(fractal->mlx.win_ptr, 4, 0, mouse_press, fractal);
}
