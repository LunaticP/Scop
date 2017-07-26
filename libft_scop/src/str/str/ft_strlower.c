/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 01:11:24 by vthomas           #+#    #+#             */
/*   Updated: 2016/10/23 01:12:52 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strlower(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		str[i] = (char)ft_tolower(str[i]);
		i++;
	}
	return (str);
}
