/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:18:14 by lhorefto          #+#    #+#             */
/*   Updated: 2021/05/14 12:09:35 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;

	result = (char *)malloc(len + 1);
	if (!s || !result)
		return (0);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		result[j++] = s[i++];
	result[j] = 0;
	return (result);
}
