/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 19:29:02 by afokin            #+#    #+#             */
/*   Updated: 2018/03/29 19:29:04 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	str_tolower(char *str)
{
	while (*str)
	{
		if (*str >= 'A' && *str <= 'F')
			*str = 'a' + *str - 'A';
		str++;
	}
}

static void	init_arr(char *arr)
{
	int i;

	i = -1;
	while (++i < 10)
		arr[i] = '0' + i;
	i = -1;
	while (++i < 6)
		arr[i + 10] = 'a' + i;
	arr[16] = 0;
}

int			ft_atoi_base(const char *str, int str_base)
{
	char		arr[17];
	long long	ret;
	int			sing;

	init_arr((char *)arr);
	str_tolower((char *)str);
	sing = -1;
	ret = 0;
	while ((*str == ' ' || *str == '\t') && *str)
		str++;
	*str != '-' ? ((sing = 1)) : (*str++);
	while (*str && ((*str - '0' <= str_base && *str - '0' >= 0) ||
	(*str - 'a' + 10 <= str_base && *str - 'a' >= 0)))
	{
		ret = ret * 10 -
		(*str >= 'a' && *str <= 'f' ? -10 + 'a' : '0') + *str;
		str++;
	}
	return (ret * sing);
}
