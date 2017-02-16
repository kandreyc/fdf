/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 13:28:50 by kandreyc          #+#    #+#             */
/*   Updated: 2017/02/11 19:22:39 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static	t_read	*new_elem(char *c)
{
	t_read	*elem;

	elem = (t_read *)malloc(sizeof(t_read));
	elem->content = *c;
	elem->next = NULL;
	return (elem);
}

static	char	*read_it(t_read *elem, int len)
{
	int		i;
	char	*str;

	i = 0;
	if (elem == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	while (elem)
	{
		str[i++] = elem->content;
		str[i] = '\0';
		elem = elem->next;
	}
	str[i] = '\0';
	return (str);
}

void			read_data(int fd, char **str, t_read *head, char *fname)
{
	int		i;
	char	buff;
	t_read	*temp;

	i = 0;
	temp = 0;
	if (read(fd, &buff, 1) != 1)
		error(fname, 2);
	head = new_elem(&buff);
	if (read(fd, &buff, 1) == 1)
	{
		temp = new_elem(&buff);
		head->next = temp;
		i += 2;
		while (read(fd, &buff, 1))
		{
			temp->next = new_elem(&buff);
			temp = temp->next;
			i++;
		}
	}
	(*str) = read_it(head, i);
	free(head);
}
