/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:02:02 by tlegendr          #+#    #+#             */
/*   Updated: 2024/05/04 23:30:23 by tlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_destroy(t_fractal *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

void	image_set_pixel(void *img_ptr, int x, int y, int color)
{
	void	*addr;
	int		bpp;

	bpp = 24;
	addr = mlx_get_data_addr(img_ptr, &bpp, &bpp, &bpp);
	*(unsigned int *)(addr + (x * 4 + y * 800 * 4)) = color;
}

int	on_key_press(int keycode, t_fractal *fractal)
{
	if (keycode == XK_Escape)
		on_destroy(fractal);
	else if (keycode == XK_Control_L)
	{
		fractal->color = get_next_color();
		render_fractal(*fractal);
	}
	return (0);
}

int	on_scroll( int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == 4)
		fractal->zoom *= 1.05;
	else if (button == 5)
		fractal->zoom *= 0.95;
	render_fractal(*fractal);
	return (0);
}

long	ft_atoi(const char *string, int *index)
{
	int		i;
	long	result;
	int		is_negative;

	i = *index;
	result = 0;
	is_negative = 0;
	while (string[i] == ' ' || string[i] == '\t' || string[i] == '\n'
		|| string[i] == '\v' || string[i] == '\f' || string[i] == '\r')
		i++;
	if (string[i] == '-')
		is_negative = 1;
	if (string[i] == '-' || string[i] == '+')
		i++;
	while (string[i] >= '0' && string[i] <= '9')
	{
		result = result * 10 + (string[i] - '0');
		i++;
	}
	if (is_negative == 1)
		return (-result);
	*index = i;
	return (result);
}
