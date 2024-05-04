/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:01:27 by tlegendr          #+#    #+#             */
/*   Updated: 2024/05/04 23:27:59 by tlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calculate_mandelbrot(int x, int y, t_fractal f)
{
	float	c[2];
	float	z[2];
	int		n;
	float	z_re_temp;

	c[0] = (x - f.width / 2.0) * 4.0 / (f.zoom * f.width);
	c[1] = (y - f.height / 2.0) * 4.0 / (f.zoom * f.height);
	z[0] = 0;
	z[1] = 0;
	n = 0;
	while (n < f.iter)
	{
		z_re_temp = z[0] * z[0] - z[1] * z[1] + c[0];
		z[1] = 2 * z[0] * z[1] + c[1];
		z[0] = z_re_temp;
		if (z[0] * z[0] + z[1] * z[1] > 4)
			return (n);
		n++;
	}
	return (f.iter);
}

double	ft_atol(const char *string)
{
	int		i;
	double	result;
	int		is_negative;
	double	decimal;
	int		decimal_count;

	i = 0;
	result = 0;
	is_negative = 1.0;
	while (string[i] == ' ' || string[i] == '\t' || string[i] == '\n'
		|| string[i] == '\v' || string[i] == '\f' || string[i] == '\r')
		i++;
	if (string[i] == '-')
		is_negative = -1.0;
	if (string[i] == '-' || string[i] == '+')
		i++;
	result = ft_atoi(&string[0], &i);
	if (string[i] == '.' || string[i] == ',')
	{
		decimal_count = ++i;
		decimal = ft_atoi(&string[0], &i);
		decimal /= pow(10, i - decimal_count);
		result += (decimal);
	}
	return (result * is_negative);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	return (0);
}

int	calculate_julia(int x, int y, t_fractal f)
{
	float	z_re;
	float	z_im;
	int		n;
	float	z_re_temp;

	z_im = (y - f.height / 2.0) * 4.0 / (f.zoom * f.height);
	z_re = (x - f.width / 2.0) * 4.0 / (f.zoom * f.width);
	n = 0;
	while (n < f.iter)
	{
		z_re_temp = z_re * z_re - z_im * z_im + f.cr;
		z_im = 2 * z_re * z_im + f.ci;
		z_re = z_re_temp;
		if (z_re * z_re + z_im * z_im > 4)
			return (n);
		n++;
	}
	return (f.iter);
}

int	get_next_color(void)
{
	static int	i = 0;
	static int	color[] = {0x050124FF, 0x090147FF, 0x040449FF,
		0x000764FF, 0x0C2C8AFF,
		0x1852B1FF, 0x397DD1FF, 0x86B5E5FF, 0xD3ECF8FF, 0xF1E9BFFF, 0xF8C95FFF,
		0xFFAA00FF, 0xCC8000FF, 0x995700FF, 0x6A3403FF};

	i++;
	if (i == 14)
		i = 0;
	return (color[i]);
}
