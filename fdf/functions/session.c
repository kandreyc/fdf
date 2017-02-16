/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:10:15 by kandreyc          #+#    #+#             */
/*   Updated: 2017/02/11 19:23:58 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static	int		hex(char *str)
{
	int		i;
	int		j;
	long	num;

	num = 0;
	i = -1;
	j = 0;
	while (str[j] != ' ' && str[j] != '\0')
		j++;
	while (str[++i])
	{
		if (str[i] > 47 && str[i] < 58)
			num += ((str[i] - 48) * pow(16, --j));
		else if (str[i] > 64 && str[i] < 71)
			num += ((str[i] - 55) * pow(16, --j));
		else if (str[i] > 96 && str[i] < 103)
			num += ((str[i] - 87) * pow(16, --j));
		else
			return (0);
	}
	return (num);
}

static int		fdf_atoi(char *str, int *k)
{
	int			num;
	int			neg;

	(*k) = 0;
	num = 0;
	neg = 1;
	if ((str[(*k)] == '-' && str[(*k) + 1] >= '0' && str[(*k) + 1] <= '9') ||
	(str[(*k)] == '+' && str[(*k) + 1] >= '0' && str[(*k) + 1] <= '9'))
	{
		if (str[(*k)] == '-')
			neg = -1;
		(*k)++;
	}
	while (str[(*k)] >= '0' && str[(*k)] <= '9')
	{
		num *= 10;
		num += ((int)str[(*k)] - 48);
		(*k)++;
	}
	return (num * neg);
}

static	t_axis	*xyz_axis(t_session *file, t_axis *xyz, char **data, int i)
{
	int		k;
	int		j;
	int		l;
	char	**tmp;

	j = -1;
	i = 0;
	l = 0;
	while (data[++j])
	{
		tmp = ft_strsplit(data[j], 32);
		k = -1;
		while (tmp[++k])
		{
			IX = k;
			IY = j;
			IZ = fdf_atoi(tmp[k], &l);
			MIN_Z = fmin(MIN_Z, IZ);
			MAX_Z = fmax(MAX_Z, IZ);
			P_COLOR = (tmp[k][l] == ',') ? hex(tmp[k] + (l + 3)) : M_COLOR;
			i++;
		}
	}
	LEN = i;
	return (xyz);
}

static	void	img_size(t_session *file, char **data, char *fname)
{
	int		i;
	int		j;
	int		check;

	i = -1;
	WIDTH = 0;
	HEIGHT = 0;
	check = 0;
	while (data[++i])
	{
		j = -1;
		WIDTH = 0;
		while (data[i][++j])
			if (data[i][j] != ' ')
			{
				WIDTH++;
				while (data[i][j + 1] != ' ' && data[i][j + 1] != '\0')
					j++;
			}
		(i == 0) ? check = WIDTH : 0;
		(check != WIDTH) ? error(fname, 2) : 0;
		HEIGHT++;
	}
}

t_session		*new_session(t_session *file, char *fname, int id, char *input)
{
	int			fd;
	char		**splinput;

	if ((fd = open(fname, O_RDONLY)) == -1)
		error(fname, 2);
	read_data(fd, &input, NULL, fname);
	close(fd);
	img_size(file, (splinput = ft_strsplit(input, 10)), fname);
	file->id = id;
	file->alpha = -60;
	file->beta = 0;
	file->gamma = 0;
	file->scale = 30;
	while ((WIDTH * SCALE) * (HEIGHT * SCALE) > (1280 * 768))
		SCALE--;
	file->min_z = 0;
	file->max_z = 0;
	file->img = NULL;
	file->color = 16777215;
	file->mlx = mlx_init();
	file->xyz = (t_axis *)malloc(sizeof(t_axis) * ((HEIGHT * WIDTH) + 1));
	file->xyz = xyz_axis(file, file->xyz, splinput, LEN);
	((WIDTH == 0 && HEIGHT == 0) || LEN < 2) ? error(fname, 2) : 0;
	file->correct_z = 1;
	return (file);
}
