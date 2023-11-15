/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 22:39:58 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/22 17:18:54 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_close(t_data *data)
{
	fdf_freearr(data);
	free(data);
	exit(0);
	return (0);
}

size_t	wordcount(const char *str, const char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while ((str[i] == c || str[i] == '\n') && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}
