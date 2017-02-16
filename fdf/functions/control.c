/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:40:40 by kandreyc          #+#    #+#             */
/*   Updated: 2017/02/11 19:22:37 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static	int			around(t_session *file)
{
	if (KEY == 126 || KEY == 125)
		ALPHA += (KEY == 126) ? -0.5 : 0.5;
	if (KEY == 124 || KEY == 123)
		GAMMA += (KEY == 124) ? -0.5 : 0.5;
	if (KEY == 116 || KEY == 121)
		file->correct_z += (KEY == 116) ? 0.01 : -0.01;
	render(file);
	return (0);
}

static	int			button_check(t_session *temp, int button)
{
	if (button == 18 && temp->id == 0)
		return (1);
	else if (button == 19 && temp->id == 1)
		return (1);
	else if (button == 20 && temp->id == 2)
		return (1);
	else if (button == 21 && temp->id == 3)
		return (1);
	else if (button == 23 && temp->id == 4)
		return (1);
	else if (button == 22 && temp->id == 5)
		return (1);
	else if (button == 26 && temp->id == 6)
		return (1);
	else if (button == 28 && temp->id == 7)
		return (1);
	else if (button == 25 && temp->id == 8)
		return (1);
	return (0);
}

static	t_session	*next_file(t_session *file, int button)
{
	int		mem;

	mem = file->id;
	while (file != NULL)
	{
		if (file->next == NULL)
			break ;
		file = file->next;
		if (button_check(file, button) == 1)
			break ;
		if (file->id == mem)
			break ;
	}
	return (file);
}

int					control(int button, t_session *file)
{
	if (button == 69 || button == 78)
		SCALE *= (button == 69) ? 1.1 : 0.9;
	else if (button == 126 || button == 125)
		KEY = (button == 126) ? 126 : 125;
	else if (button == 123 || button == 124)
		KEY = (button == 124) ? 124 : 123;
	else if (button == 49)
		KEY = 49;
	else if (button > 17 && button < 30 && button != 24 && button != 27)
		file = next_file(file, button);
	else if (button == 116 || button == 121)
		KEY = (button == 116) ? 116 : 121;
	else if (button == 53)
		error("Program has been closed\n", 1);
	else if (button != -42)
		return (error("Wrong button!\n", 0));
	mlx_key_hook(WIN, control, file);
	mlx_loop_hook(file->mlx, around, file);
	mlx_loop(MLX);
	return (0);
}
