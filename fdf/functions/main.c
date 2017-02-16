/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 14:08:33 by kandreyc          #+#    #+#             */
/*   Updated: 2017/02/11 19:22:39 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static	t_session	*new_list(t_session *file, int ac, char **av)
{
	int			i;
	t_session	*temp;

	i = 1;
	temp = (t_session *)malloc(sizeof(t_session));
	temp = new_session(temp, av[2], i, NULL);
	temp->win = WIN;
	temp->mlx = MLX;
	file->next = temp;
	while (++i < ac)
	{
		temp->next = (t_session *)malloc(sizeof(t_session));
		temp->next = new_session(temp->next, av[i + 1], i, NULL);
		temp->next->win = WIN;
		temp->next->mlx = MLX;
		temp = temp->next;
	}
	temp->next = file;
	return (file);
}

int					main(int ac, char **av)
{
	t_session	*file;
	void		*win;

	if (ac < 2 && ac > 9)
		error("No input file\n", 1);
	file = (t_session *)malloc(sizeof(t_session));
	file = new_session(file, av[1], 0, NULL);
	win = mlx_new_window(MLX, 1280, 768, "FdF");
	file->win = win;
	if (ac > 2)
		file = new_list(file, ac - 1, av);
	control(-42, file);
	return (0);
}
