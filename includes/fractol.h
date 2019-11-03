
#ifndef FRACTOL_H
#define FRACTOL_H

#define WIN_WIDTH 1200
#define WIN_HEIGHT 900
// 270 * 240
#define PTHREADS 12

typedef struct s_mouse
{
    int x;
    int y;
} t_mouse;

typedef struct s_img
{
    void *img_ptr;
    int *data;
    int size_l;
    int bpp;
    int endian;
} t_img;

typedef struct s_mlx
{
    void *mlx_ptr;
    void *win_ptr;
    t_img img;
} t_mlx;

typedef struct s_fractal
{
    unsigned int fractal_nb;
    unsigned int pthread_nb;
    unsigned int i_max;
    unsigned int i;
    double zoom_x;
    double zoom_y;
    double x;
    double y;
    double x1;
    double x2;
    double y1;
    double y2;
    double c_r;
    double c_i;
    double z_r;
    double z_i;
    double tmp;
    t_mouse mouse;
    t_mlx mlx;
} t_fractal;

void draw(t_fractal *fractal);
void mandelbrot_init(t_fractal *f);
void mandelbrot_pthread(t_fractal *f);
void julia_init(t_fractal *f);
void julia_pthread(t_fractal *f);
void tricorn_init(t_fractal *f);
void tricorn_pthread(t_fractal *f);
void burningship_init(t_fractal *f);
void burningship_pthread(t_fractal *f);
int key_press(int key, void *param);
int mouse_press(int button, int x, int y, void *param);
int mouse_bis(int button, int x, int y, void *param);
void ft_display_window(t_mlx *mlx, char *title, int img_width, int img_height);
void point_to_img(t_fractal *fractal, int x, int y, int color);
void setup_controls(t_fractal *fractal);

#endif
