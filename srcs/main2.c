/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 16:18:47 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/08/06 16:18:49 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int check_input2(int ac, char **argv)
{
    if (ac < 2)
    {
        ft_printf("usage :\n\tmandelbrot\n\tjulia\n\ttricorn\n\tbunringship\n");
        return (-1);
    }
    if (ac >= 2)
    {
        if (ft_strequ(argv[1], "mandelbrot") || ft_strequ(argv[1], "julia") || ft_strequ(argv[1], "tricorn") || ft_strequ(argv[1], "burningship"))
        {
            if (ac == 3)
            {
                if (ft_strequ(argv[2], "mandelbrot") || ft_strequ(argv[2], "julia") || ft_strequ(argv[2], "tricorn") || ft_strequ(argv[2], "burningship"))
                    return (0);
            }
        }
    }
    return (0);
}

void fractal_init(char *fractal_name, t_fractal *f)
{
    if (ft_strequ(fractal_name, "mandelbrot"))
        mandelbrot_init(f);
    if (ft_strequ(fractal_name, "julia"))
        julia_init(f);
    if (ft_strequ(fractal_name, "tricorn"))
        tricorn_init(f);
    if (ft_strequ(fractal_name, "burningship"))
        burningship_init(f);
}

void draw(t_fractal *fractal)
{
    mlx_destroy_image(fractal->mlx.mlx_ptr, fractal->mlx.img.img_ptr);
    fractal->mlx.img.img_ptr =
        mlx_new_image(fractal->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    fractal->mlx.img.data =
        (int *)mlx_get_data_addr(fractal->mlx.img.img_ptr, &(fractal->mlx.img.bpp),
                                 &(fractal->mlx.img.size_l), &(fractal->mlx.img.endian));
    if (fractal->fractal_nb == 1)
        mandelbrot_pthread(fractal);
    if (fractal->fractal_nb == 2)
        julia_pthread(fractal);
    if (fractal->fractal_nb == 3)
        tricorn_pthread(fractal);
    if (fractal->fractal_nb == 4)
        burningship_pthread(fractal);
}

int main2(int ac, char **argv)
{
    int n;
    t_fractal fractal;
    // t_fractal fractal[ac];

    if (check_input(ac, argv) == -1)
        return (-1);
    ft_display_window(&(fractal.mlx), argv[1], WIN_WIDTH, WIN_HEIGHT);
    fractal_init(argv, &fractal);
    draw(&fractal);
    setup_controls(&fractal);
    mlx_loop(fractal.mlx.mlx_ptr);
    return (0);
}
