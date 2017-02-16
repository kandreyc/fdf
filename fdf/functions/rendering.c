/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:31:14 by kandreyc          #+#    #+#             */
/*   Updated: 2017/02/11 19:22:40 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

#define SIN_A	sin(file->alpha * RAD)
#define COS_A	cos(file->alpha * RAD)
#define SIN_B	sin(file->beta * RAD)

#define COS_B	cos(file->beta * RAD)
#define SIN_G	sin(file->gamma * RAD)
#define COS_G	cos(file->gamma * RAD)

#define X0		file->xyz[LEN - 1].input_x / 2
#define Y0		file->xyz[LEN - 1].input_y / 2

static	void		new_image(t_session *file)
{
	file->end = 0;
	file->bbp = 32;
	file->img = mlx_new_image(MLX, 1281, 769);
	file->data = mlx_get_data_addr(IMG, &BBP, &SIZELINE, &END);
}

static	void		mapping(t_session *file)
{
	int		i;
	int		line;
	int		skip;

	i = 0;
	skip = 0;
	line = WIDTH;
	while (i < LEN)
	{
		skip = (i < line) ? 0 : (i / line) * line;
		if ((i - skip) + 1 < line)
			pre_straight(file, file->xyz[i], file->xyz[i + 1]);
		if ((i + line) < LEN)
			pre_straight(file, file->xyz[i], file->xyz[i + line]);
		i++;
	}
}

static	void		compute(t_session *file)
{
	int		i;
	int		min_max_z[2];

	i = -1;
	min_max_z[0] = file->min_z * SCALE;
	min_max_z[1] = file->max_z * SCALE;
	while (++i < LEN)
	{
		OX = ceil(((IX * SCALE) - (X0 * SCALE)) * COS_G) -
		(((IY * SCALE) - (Y0 * SCALE)) * SIN_G);
		OY = ceil(((IX * SCALE) - (X0 * SCALE)) * SIN_G) +
		(((IY * SCALE) - (Y0 * SCALE)) * COS_G);
		OZ = (IZ * SCALE * file->correct_z);
		OX = ceil((COS_B * OX) - (SIN_B * OZ) + 640);
		OY = ceil((SIN_A * SIN_B * OX) + (COS_A * OY) +
			(SIN_A * COS_B * OZ) + 384) + ((MAX_Z + fabs(MIN_Z)) / 2);
	}
}

void				render(t_session *file)
{
	(file->img) ? mlx_destroy_image(file->mlx, file->img) : 0;
	compute(file);
	new_image(file);
	mapping(file);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
}
