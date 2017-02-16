/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 20:35:28 by kandreyc          #+#    #+#             */
/*   Updated: 2017/02/11 19:22:38 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static	void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static	void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

int				error(char *msg, int esc)
{
	if (esc == 2)
	{
		ft_putstr("Input file [");
		ft_putstr(msg);
		ft_putstr("] is not valid\n");
	}
	else
		ft_putstr(msg);
	if (esc == 1 || esc == 2)
		exit(0);
	return (0);
}
