#include "fractol.h"

void        fractInit(t_fract *fract)
{
    fract->zoom = 0.99;
    fract->rsx = -1.6;
    fract->rex = 0.5;
    fract->rsy = 0.866;
    fract->rey = -0.866;
    fract->maxIter = 100;
    fract->mlx = ft_memalloc(sizeof(t_mlx));
    

}

void        mlxInit(t_mlx *mlx)
{
    mlx->mlxptr = mlx_init();
    mlx->winptr = mlx_new_window(mlx->mlxptr, WIDTH, HEIGHT,"fractol"); 
    mlx->imgptr = mlx_new_image(mlx->mlxptr, WIDTH, HEIGHT);
    mlx->imgstr = (unsigned char *)mlx_get_data_addr(mlx->imgptr, &mlx->bpp, &mlx->size_l, &mlx->endian);
}

int         julia(double A, double B, int maxIter)
{
    double  zr = A;
    double  zi = B;
    double  tmp = 0;
    int     n = -1;
    while ( ++n < maxIter) 
    {
        tmp = zr * zr - zi * zi;
        zi = 2 * zr * zi  +  0.156 ;
        zr = tmp +  -0.8;
        if (POW(zr) + POW(zi) > 4)
            break;
    }
        return n;
}

void        img_pixel_put(t_mlx *mlx, int x, int y, int n)
{
    int     i;

    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    i = x * 4 + y * WIDTH * 4;
    if (n == MAXITER)
    {
        mlx->imgstr[i] = (unsigned char)0;
        mlx->imgstr[i + 1] = (unsigned char)0;
        mlx->imgstr[i + 2] = (unsigned char)0;
    }
    else
    {
        mlx->imgstr[i] = (unsigned char)((int)n * 3);
        mlx->imgstr[i + 1] = (unsigned char)((int)n * 2);
        mlx->imgstr[i + 2] = (unsigned char)((int)n * n);
    }   
}

int         mandelbrot(double A, double B, int maxIter)
{
    double  zr = A;
    double  zi = B;
    double  tmp = 0;
    int     n = -1;

    while (++n < maxIter)
    {
        if (POW(zr) + POW(zi) > 4)
            return n;
        tmp = POW(zr) - POW(zi) + A;
        zi = 2 * (zr * zi) + B;
        zr = tmp;
    }
    return n;
}

void        draw(t_fract *fract)
{
    int     x = -1;
    int     y = -1;
    double  rx = 0;
    double  ry = 0;
    int     n = 0;

    while (++x < WIDTH)
    {
        rx = (x / (WIDTH/ABS((fract->rex - fract->rsx)))) + fract->rsx;
        y = -1;
        while (++y < HEIGHT)
        {
            ry = (y / (HEIGHT/ABS((fract->rey - fract->rsy)))) - fract->rsy;
            n = mandelbrot(rx,ry,fract->maxIter);
            img_pixel_put(fract->mlx, x, y, n);
        }  
    }
}

int         ft_mouse_press(int button, int x, int y,t_fract *fract)
{
    long double zoom;
    printf(" button : %d , x : %d || y : %d\n", button, x, y);
    if(button == 5)
    {
        x = (x / (WIDTH/ABS((fract->rex - fract->rsx)))) + fract->rsx;
        y = (y / (HEIGHT/ABS((fract->rey - fract->rsy)))) - fract->rsy;
        fract->rsx = x + ((fract->rsx - x) * fract->zoom);
        fract->rsy = y + (fract->rsy - y) * fract->zoom;
        fract->rex = x + ((fract->rex - x) * fract->zoom);
        fract->rey = y + (fract->rey - y) * fract->zoom;
    }
    if(button == 4)
    {
        printf(" before  button : %d , rsx : %lf || rex : %lf\n", button, fract->rsx, fract->rex);
        x = (x / (WIDTH/ABS((fract->rex - fract->rsx)))) + fract->rsx;
        fract->rsx = x + ((fract->rsx - x) / fract->zoom);
        fract->rex = x + ((fract->rex - x) / fract->zoom);
        printf(" after button : %d , rsx : %lf || rex : %lf\n", button, fract->rsx, fract->rex);
        printf(" before abutton : %d , rsy : %lf || rey : %lf\n", button, fract->rsy, fract->rey);
        y = (y / (HEIGHT/ABS((fract->rey - fract->rsy)))) - fract->rsy;
        fract->rsy = y + (fract->rsy - y) / fract->zoom;
        fract->rey = y + (fract->rey - y) / fract->zoom;
       
        printf(" after button : %d , rsy : %lf || rey : %lf\n", button, fract->rsy, fract->rey);
    }
    if (button == 1)
    {
        fract->rsx = -1.6;
        fract->rex = 0.5;
        fract->rsy = 0.866;
        fract->rey = -0.866;
        fract->maxIter = 100;
    }
        ft_bzero(fract->mlx->imgstr, WIDTH * HEIGHT * sizeof (unsigned char));
        draw(fract);
        mlx_put_image_to_window(fract->mlx->mlxptr, fract->mlx->winptr, fract->mlx->imgptr, 0, 0);
    return 0;
}

int         main(ac,av)
int         ac;
char        **av;
{
    t_fract *fract;
    
    fract = ft_memalloc(sizeof(t_fract));
    fractInit(fract);
    mlxInit(fract->mlx);
    draw(fract);
    mlx_put_image_to_window(fract->mlx->mlxptr, fract->mlx->winptr, fract->mlx->imgptr, 0, 0);
    mlx_mouse_hook(fract->mlx->winptr,ft_mouse_press,fract);
    mlx_loop(fract->mlx->mlxptr);
    return (0);
}
