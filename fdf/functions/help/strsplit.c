/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 17:23:33 by kandreyc          #+#    #+#             */
/*   Updated: 2017/02/11 17:49:45 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static	char	**mem_free(char **new, int lvl)
{
	int		k;

	k = 0;
	while (k < lvl)
		free(new[k++]);
	free(new);
	return (NULL);
}

static	int		deep_counter(const char *s, char c)
{
	int		k;
	int		i;
	int		delim;

	i = 0;
	k = -1;
	delim = 0;
	while (s[++k])
		if (s[k] == c)
			delim++;
	if (delim == k)
		return (i);
	if (s[0] != c)
		i += 1;
	k = 1;
	while (s[k])
	{
		if (s[k - 1] == c && s[k] != c)
		{
			i++;
		}
		k++;
	}
	return (i);
}

static	char	*fill_lvl(char *s, char c, int *start)
{
	int		i;
	int		len;
	char	*new;

	i = *start - 1;
	len = 0;
	while (s[++i] != c && s[i] != '\0')
		len++;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
		new[i++] = s[(*start)++];
	new[i] = '\0';
	return (new);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**new;
	int		lvl;
	int		start;
	int		deep;

	lvl = -1;
	start = 0;
	if (!s)
		return (NULL);
	deep = deep_counter(s, c);
	new = (char **)malloc(sizeof(char *) * (deep + 1));
	if (!new)
		return (NULL);
	while (++lvl <= deep)
	{
		while (s[start] == c)
			start++;
		new[lvl] = fill_lvl((char*)s, c, &start);
		if (new[lvl] == NULL)
			return (mem_free(new, lvl));
	}
	new[deep] = 0;
	return (new);
}
