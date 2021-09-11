/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:17:03 by lhorefto          #+#    #+#             */
/*   Updated: 2021/05/13 13:47:00 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	dest = NULL;
	i = 0;
	dest = (char *)malloc(ft_strlen(src) + 1);
	if (dest == NULL)
		return (0);
	while (src[i])
	{
		dest[i] = ((char *)src)[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
