/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:06:06 by tlegendr          #+#    #+#             */
/*   Updated: 2024/05/04 23:32:27 by tlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_fractal
{
	char	*name;
	int		x;
	int		y;
	double	cr;
	double	ci;
	int		color;
	float	zoom;
	int		iter;
	int		width;
	int		height;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_fractal;

void	ft_putstr(char *str);
void	init_fractal(int argc, char **argv, t_fractal *fractal);
void	render_fractal(t_fractal fractal);
int		map_iter_to_color(int iter, t_fractal *fractal);

int		calculate_mandelbrot(int x, int y, t_fractal fractal);
double	ft_atol(const char *string);
int		ft_strcmp(const char *s1, const char *s2);
int		calculate_julia(int x, int y, t_fractal fractal);
int		get_next_color(void);

int		on_destroy(t_fractal *data);
void	image_set_pixel(void *img_ptr, int x, int y, int color);
int		on_key_press(int keycode, t_fractal *fractal);
int		on_scroll( int button, int x, int y, t_fractal *fractal);
long	ft_atoi(const char *string, int *index);

#endif