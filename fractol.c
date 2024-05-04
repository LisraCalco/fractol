/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:29:00 by tlegendr          #+#    #+#             */
/*   Updated: 2024/05/04 23:31:46 by tlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	map_iter_to_color(int iter, t_fractal *fractal)
{
	if (iter == fractal->iter)
		return (0x000000);
	return (iter * fractal->color - 67);
}

void	render_fractal(t_fractal fractal)
{
	int	x;
	int	y;
	int	color;
	int	iter;

	y = -1;
	while (y++ < 800)
	{
		x = -1;
		while (++x < 800)
		{
			if (ft_strcmp(fractal.name, "julia") == 0)
				iter = calculate_julia(x, 800 - y, fractal);
			else if (ft_strcmp(fractal.name, "mandelbrot") == 0)
				iter = calculate_mandelbrot(x, y, fractal);
			color = 0x000000;
			if (iter != fractal.iter)
				color = map_iter_to_color(iter, &fractal);
			image_set_pixel(fractal.img_ptr, x, y, color);
		}
	}
	mlx_put_image_to_window(fractal.mlx_ptr, fractal.win_ptr,
		fractal.img_ptr, 0, 0);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	init_fractal(int argc, char **argv, t_fractal *fractal)
{
	fractal->name = argv[1];
	fractal->zoom = 1;
	fractal->iter = 50;
	fractal->color = 0x111111;
	fractal->cr = 0.285;
	fractal->ci = 0.01;
	fractal->width = 800;
	fractal->height = 800;
	fractal->mlx_ptr = mlx_init();
	fractal->img_ptr = mlx_new_image(fractal->mlx_ptr, 800, 800);
	fractal->win_ptr = mlx_new_window(fractal->mlx_ptr, 800, 800, "fractol");
	if (argc == 4)
	{
		fractal->cr = ft_atol(argv[2]);
		fractal->ci = ft_atol(argv[3]);
	}
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (argc < 2 || argc > 4)
	{
		ft_putstr("Usage: ./fractol [mandelbrot/julia] [real] [imaginary]\n");
		return (1);
	}
	if (ft_strcmp(argv[1], "mandelbrot") != 0
		&& ft_strcmp(argv[1], "julia") != 0)
	{
		ft_putstr("Usage: ./fractol [mandelbrot/julia] [real] [imaginary]\n");
		return (1);
	}
	init_fractal(argc, argv, &fractal);
	mlx_mouse_hook(fractal.win_ptr, &on_scroll, &fractal);
	mlx_key_hook(fractal.win_ptr, &on_key_press, &fractal);
	mlx_hook(fractal.win_ptr, DestroyNotify,
		StructureNotifyMask, &on_destroy, &fractal);
	render_fractal(fractal);
	mlx_loop(fractal.mlx_ptr);
	return (0);
}
