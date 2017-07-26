/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stroccur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 19:31:19 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/21 19:38:52 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_stroccur(char *str, char a, char b)
{
	char	*tmp;

	while ((tmp = ft_strchr(str, a)))
		*tmp = b;
	if (str[ft_strlen(str)] == '\n')
		str[ft_strlen(str)] = '\0';
	return (str);
}
