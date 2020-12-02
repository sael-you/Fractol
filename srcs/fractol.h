#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# define WIDTH 500
# define HEIGHT 500
# define MAXITER 100
# define ABS(x) (x > 0 ? x: -x)
# define POW(x) (x * x)


typedef struct       s_mlx
{
    void             *mlxptr;
    void             *imgptr;
    void             *winptr;
    unsigned char    *imgstr;
    int		         size_l;
    int		         bpp;
    int		         endian;
}                    t_mlx;

typedef struct      s_fract
{
    double          zoom;
    double          rx;
    double          ry;
    double          rsx;
    double          rex;
    double          rsy;
    double          rey;
    int             maxIter;
    t_mlx           *mlx;
}                   t_fract;

void                fractInit(t_fract *fract);
void                mlxInit(t_mlx *mlx);
int                 mandelbrot(double A, double B, int maxIter);
int                 julia(double A, double B, int maxIter);
void                img_pixel_put(t_mlx *mlx, int x, int y, int n);
int                 ft_mouse_press(int button, int x, int y, t_fract *fract);
void                draw(t_fract *fract);



#endif