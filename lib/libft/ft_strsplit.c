/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:09:16 by afokin            #+#    #+#             */
/*   Updated: 2017/10/30 18:09:20 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_splitsub(char *s, int len)
{
	char	*ptr;
	int		i;

	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (i < len && s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

static int	arrnum(char *s, char c)
{
	int	count;

	count = 0;
	if (*s != c)
		count++;
	if (*s)
		s++;
	while (*s)
	{
		if (*s != c && *(s - 1) == c)
			count++;
		s++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**rtn;
	int		i;
	int		j;

	if (!s)
		return (0);
	rtn = (char **)malloc(sizeof(char *) * (arrnum((char *)s, c) + 1));
	if (!rtn)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		j = 0;
		while (s[j] && s[j] != c)
			j++;
		if (!(rtn[i] = ft_splitsub((char *)s, j)))
			return (0);
		s += j;
		if (j)
			i++;
	}
	rtn[i] = 0;
	return (rtn);
}
