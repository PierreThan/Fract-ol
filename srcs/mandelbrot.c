/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 16:18:47 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/08/06 16:18:49 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// https://www.geeksforgeeks.org/multithreading-c-2/
// https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514567-les-threads
// https://stackoverflow.com/questions/1718465/optimal-number-of-threads-per-core
// http://sdz.tdct.org/sdz/dessiner-la-fractale-de-mandelbrot.html
// https://franckh.developpez.com/tutoriels/posix/pthreads/

void mandelbrot_init(t_fractal *f)
{
    f->fractal_nb = 1;
    f->x1 = -2.1;
    f->x2 = 0.6;
    f->y1 = -1.2;
    f->y2 = 1.2;
    f->i_max = 100;
    // f->i_max = 50;
    //f->zoom = 100; pour 270*240
    f->zoom_x = WIN_WIDTH / (f->x2 - f->x1);
    f->zoom_y = WIN_HEIGHT / (f->y2 - f->y1);
}

void mandelbrot_iteration(t_fractal *f)
{
    f->c_r = f->x / f->zoom + f->x1;
    f->c_i = f->y / f->zoom + f->y1;
    f->z_r = 0;
    f->z_i = 0;
    f->i = 0;
    while (f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->i_max)
    {
        f->tmp = f->z_r;
        f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
        f->z_i = 2 * f->z_i * f->tmp + f->c_i;
        f->i = f->i + 1;
    }
    if (f->i == f->i_max)
        point_to_img(f, f->x, f->y, 0x000000);
    else
        point_to_img(f, f->x, f->y, f->i * 255 / f->i_max);
}

void mandelbrot(t_fractal *f)
{
    f->x = (double)f->pthread_nb;
    while (f->x < WIN_WIDTH)
    {
        f->y = -1;
        while (++f->y < WIN_HEIGHT)
            mandelbrot_iteration(f);
        f->x += PTHREADS;
    }
}

void mandelbrot_pthread(t_fractal *f)
{
    unsigned int n;
    t_fractal f_tab[PTHREADS];
    pthread_t t[PTHREADS];

    n = 0;
    while (n < PTHREADS)
    {
        ft_memcpy((void *)&f_tab[n], (void *)f, sizeof(t_fractal));
        f_tab[n].pthread_nb = n;
        if (pthread_create(&t[n], NULL, mandelbrot, &f_tab[n]))
        {
            exit(0);
        }
        n++;
    }
    while (n--)
        pthread_join(t[n], NULL);
    mlx_put_image_to_window(f->mlx.mlx_ptr, f->mlx.win_ptr, f->mlx.img.img_ptr, 0, 0);
}
