#include <pthread.h>
#include "fractol.h"
#define PTHREADS 12

// https://www.geeksforgeeks.org/multithreading-c-2/
// https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514567-les-threads
// https://stackoverflow.com/questions/1718465/optimal-number-of-threads-per-core

void julia_init(t_fractal *f)
{
    f->fractal_nb = 2;
    f->x1 = -1;
    f->x2 = 1;
    f->y1 = -1.2;
    f->i_max = 100;
    //f->i_max = 50;
    //f->zoom = 100;
    f->zoom_x = WIN_WIDTH / (f->x2 - f->x1);
    f->zoom_y = WIN_HEIGHT / (f->y2 - f->y1);
    f->c_r = f->x / f->zoom_x + f->x1;
    f->c_i = f->y / f->zoom_y + f->y1;
}

void julia_iteration(t_fractal *f)
{
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

void julia(t_fractal *f) //void julia(void *f) avec f à caster en t_fractal
{
    f->x = f->pthread_nb; // passable dans julia_pthread
    while (f->x < WIN_WIDTH)
    {
        f->y = -1;
        while (++f->y < WIN_HEIGHT)
        {
            f->z_r = f->x / f->zoom + f->x1;
            f->z_i = f->y / f->zoom + f->y1;
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
                point_to_img(f, f->x, f->y, 255 * f->i / f->i_max);
        }
        f->x += PTHREADS;
    }
}

void julia_pthread(t_fractal *f)
{
    unsigned int n;
    t_fractal f_tab[PTHREADS];
    pthread_t t[PTHREADS];

    n = 0;
    while (n < PTHREADS)
    {
        ft_memcpy((void *)&f_tab[n], (void *)f, sizeof(t_fractal));
        f_tab[n].pthread_nb = n;
        pthread_create(&t[n], NULL, julia, &f_tab[n]);
        n++;
    }
    while (n--)
        pthread_join(t[n], NULL);
    mlx_put_image_to_window(f->mlx.mlx_ptr, f->mlx.win_ptr, f->mlx.img.img_ptr, 0, 0);
}
