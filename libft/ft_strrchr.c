/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:17:52 by lhorefto          #+#    #+#             */
/*   Updated: 2021/05/13 13:47:43 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	size_t	i;

	tmp = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			tmp = (char *)s + i;
		i++;
	}
	if (s[i] == c)
		tmp = (char *)s + i;
	return (tmp);
}
