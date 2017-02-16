/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   straight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 12:07:52 by kandreyc          #+#    #+#             */
/*   Updated: 2017/02/11 19:23:14 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

#define R			file->rgb[2]
#define G			file->rgb[1]
#define B			file->rgb[0]

#define MIN_R		file->min_rgb[2]
#define MIN_G		file->min_rgb[1]
#define MIN_B		file->min_rgb[0]

#define MAX_R		file->max_rgb[2]
#define MAX_G		file->max_rgb[1]
#define MAX_B		file->max_rgb[0]

#define X			file->xyk[0]
#define Y			file->xyk[1]
#define K			file->xyk[2]

#define MIN_X		file->min_max_x[0]
#define MAX_X		file->min_max_x[1]

#define MIN_Y		file->min_max_y[0]
#define MAX_Y		file->min_max_y[1]

#define MIN_COLOR	file->min_max_color[0]
#define MAX_COLOR	file->min_max_color[1]

#define DELTA_Y		(fabs((MAX_Y - MIN_Y)) / fabs((MAX_X - MIN_X)))
#define DELTA_X		(fabs((MAX_X - MIN_X)) / fabs((MAX_Y - MIN_Y)))

#define SCREEN		X <= 1280 && Y <= 768 && X >= 0 && Y >= 0
#define COLOR		MIN_COLOR != MAX_COLOR

static	void	pixel_to_image(t_session *file, int x, int y)
{
	int		i;

	i = (y * SIZELINE) + (x * 4);
	file->data[i] = B;
	file->data[i + 1] = G;
	file->data[i + 2] = R;
}

static	void	gradient(t_session *file, float min, float max, float cur)
{
	R = (MIN_R + (((MAX_R - MIN_R) * (cur - min)) / (max - min)));
	G = (MIN_G + (((MAX_G - MIN_G) * (cur - min)) / (max - min)));
	B = (MIN_B + (((MAX_B - MIN_B) * (cur - min)) / (max - min)));
}

static	void	straight(t_session *file)
{
	X = MIN_X;
	Y = MIN_Y;
	if (MIN_X == MAX_X)
		while (Y != MAX_Y)
		{
			(SCREEN && COLOR) ? gradient(file, MIN_Y, MAX_Y, Y) : 0;
			(SCREEN) ? pixel_to_image(file, X, Y) : 0;
			Y = (MIN_Y < MAX_Y) ? Y + 1 : Y - 1;
		}
	else if ((K = DELTA_Y) <= 1)
		while (X != MAX_X)
		{
			Y = (MIN_Y < MAX_Y) ? Y + K : Y - K;
			(SCREEN && COLOR) ? gradient(file, MIN_X, MAX_X, X) : 0;
			(SCREEN) ? pixel_to_image(file, X, Y) : 0;
			X = (MIN_X < MAX_X) ? X + 1 : X - 1;
		}
	else if ((K = DELTA_X) <= 1)
		while (Y != MAX_Y)
		{
			X = (MIN_X < MAX_X) ? X + K : X - K;
			(SCREEN && COLOR) ? gradient(file, MIN_X, MAX_X, X) : 0;
			(SCREEN) ? pixel_to_image(file, X, Y) : 0;
			Y = (MIN_Y < MAX_Y) ? Y + 1 : Y - 1;
		}
}

void			pre_straight(t_session *file, t_axis min, t_axis max)
{
	MIN_R = ((min.color & 0xFF0000) >> 16);
	MIN_G = ((min.color & 0xFF00) >> 8);
	MIN_B = ((min.color & 0xFF));
	MAX_R = ((max.color & 0xFF0000) >> 16);
	MAX_G = ((max.color & 0xFF00) >> 8);
	MAX_B = ((max.color & 0xFF));
	if (min.color == max.color)
	{
		R = MIN_R;
		G = MIN_G;
		B = MIN_B;
	}
	MIN_X = min.output_x;
	MAX_X = max.output_x;
	MIN_Y = min.output_y;
	MAX_Y = max.output_y;
	MIN_COLOR = min.color;
	MAX_COLOR = max.color;
	straight(file);
}
