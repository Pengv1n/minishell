/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:36:40 by aregenia          #+#    #+#             */
/*   Updated: 2021/10/14 17:17:59 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*temp;
	char	*pointer;

	pointer = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!pointer)
		return (NULL);
	temp = pointer;
	while (*s)
	{
		*temp = *s;
		temp++;
		s++;
	}
	*temp = '\0';
	return (pointer);
}
