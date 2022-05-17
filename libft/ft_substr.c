/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:39:33 by aregenia          #+#    #+#             */
/*   Updated: 2021/10/14 17:55:57 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	int			a;
	size_t		length;

	a = 0;
	length = ft_strlen(s);
	if (start > length)
		len = 0;
	if ((length - start) < len)
		len = length - start;
	substr = malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	while (len)
	{
		substr[a] = s[start];
		start++;
		a++;
		len--;
	}
	substr[a] = '\0';
	return (substr);
}
