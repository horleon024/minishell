/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:17:21 by lhorefto          #+#    #+#             */
/*   Updated: 2021/05/13 13:47:05 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;

	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	result = (char *)malloc(len_s1 + len_s2 + 1);
	if (result == NULL)
		return (result);
	ft_memcpy(result, s1, len_s1);
	ft_memcpy(result + len_s1, s2, len_s2);
	*(result + len_s1 + len_s2) = '\0';
	return (result);
}
