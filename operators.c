/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:04 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/06 11:37:37 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_and(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '&' && str[i + 1] == '&')
			return (1);
		i++;
	}
	return (0);
}

/* Splits the command string from places where there is a ; or
	&& operator, executes each portion separately */

void	sc_section(char *line)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(line) + 1));
	i = 0;
	while (i < (int)ft_strlen(line))
	{
		j = 0;
		while (line[i] != ';' && line[i] != '\0'
			&& !(line[i] == '&' && line[i + 1] == '&'))
		{
			str[j] = line[i];
			i++;
			j++;
		}
		str[j] = '\0';
		if (line[i] == ';')
			i++;
		else if (line[i] == '&' && line[i + 1] == '&')
			i += 2;
		ft_exec_command(str);
	}
}

/* Checks for ; or && in the command */

void	split_operator(char *line)
{
	if (contains_and(line))
		sc_section(line);
	else
		ft_exec_command(line);
}
