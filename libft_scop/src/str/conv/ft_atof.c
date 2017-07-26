/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 19:41:40 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/19 10:08:08 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

int		dec_num(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		i++;
	return (i);
}

float	ft_atof(char *str)
{
	char	*dot;
	float	ent;
	float	dec;
	float	ret;
	int		i;

	dot = ft_strchr(str, '.');
	if (dot == NULL)
		return ((float)ft_atoi(str));
	ent = ft_atoi(str);
	ent = (ent < 0.0f) ? -ent : ent;
	dec = ft_atoi(&dot[1]);
	ret = ent;
	ret += (float)dec / (float)ft_pow(10, dec_num(&dot[1]));
	i = 0;
	while (str[i] != '\0' && !ft_isdigit(str[i]))
	{
		if (str[i] == '-')
			ret = -ret;
		i++;
	}
	return (ret);
}
