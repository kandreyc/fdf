/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:15:10 by kandreyc          #+#    #+#             */
/*   Updated: 2017/02/11 18:51:34 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"

# define RAD		0.0174533

# define KEY		file->key
# define WIN		file->win
# define MLX		file->mlx
# define IMG		file->img
# define END		file->end
# define BBP		file->bbp
# define XYZ		file->xyz
# define LEN		file->len
# define WIDTH		file->width
# define HEIGHT		file->height
# define ALPHA		file->alpha
# define BETA		file->beta
# define GAMMA		file->gamma
# define M_COLOR	file->color
# define SCALE		file->scale
# define MIN_Z		file->min_z
# define MAX_Z		file->max_z
# define SIZELINE	file->sizeline

# define IX			file->xyz[i].input_x
# define IY			file->xyz[i].input_y
# define IZ			file->xyz[i].input_z
# define OX			file->xyz[i].output_x
# define OY			file->xyz[i].output_y
# define OZ			file->xyz[i].output_z
# define P_COLOR	file->xyz[i].color

typedef struct			s_read
{
	char				content;
	struct s_read		*next;
}						t_read;

typedef	struct			s_axis
{
	float				input_x;
	float				input_y;
	float				input_z;
	float				output_x;
	float				output_y;
	float				output_z;
	int					color;
}						t_axis;

typedef struct			s_session
{
	int					id;
	int					key;

	int					width;
	int					height;

	void				*win;
	void				*mlx;
	void				*img;
	char				*data;

	int					color;
	int					end;
	int					bbp;
	int					sizeline;

	float				alpha;
	float				beta;
	float				gamma;

	float				scale;
	float				min_z;
	float				max_z;
	float				correct_z;
	unsigned char		rgb[3];
	unsigned char		min_rgb[3];
	unsigned char		max_rgb[3];
	float				min_max_y[2];
	float				min_max_x[2];
	float				min_max_color[2];
	t_axis				*xyz;
	float				xyk[3];
	int					len;
	struct s_session	*next;
}						t_session;

void					read_data
						(int fd, char **str, t_read *head, char *fname);
t_session				*new_session
						(t_session *file, char *fname, int id, char *input);
void					render(t_session *file);
int						control(int button, t_session *file);
void					pre_straight(t_session *file, t_axis min, t_axis max);
int						error(char *msg, int esc);
char					**ft_strsplit(char const *s, char c);

#endif
