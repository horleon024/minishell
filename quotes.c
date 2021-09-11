/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 22:31:45 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/05 22:31:46 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outer_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			return (2);
		if (line[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

char	*remove_quotes(char *line)
{
	int	i;
	int	q;

	i = 0;
	while (line[i] && line[i] != '"' && line[i] != 39)
		i++;
	while (line[i])
	{
		q = line[i];
		line = ft_strdel(line, i);
		while (line[i] != q)
			i++;
		line = ft_strdel(line, i);
		while (line[i] && line[i] != '"' && line[i] != 39)
			i++;
	}
	return (line);
}

void	change_quote_status(int *q, int *exit, int *i)
{
	if (*q == 0)
		*q = 1;
	else
		*q = 0;
	(*i)++;
	*exit = 2;
}

/* Returns 0 on no quotes, 1 on syntax error and 2 on even number of quotes */

int	count_quotes(char *line, int q, int i, int exit)
{
	while (line[i])
	{
		if (line[i] == 39)
		{
			change_quote_status(&q, &exit, &i);
			while (line[i] && line[i] != 39)
				i++;
			if (line[i] == 39)
				change_quote_status(&q, &exit, &i);
		}
		else if (line[i] == '"')
		{
			change_quote_status(&q, &exit, &i);
			while (line[i] && line[i] != '"')
				i++;
			if (line[i] == '"')
				change_quote_status(&q, &exit, &i);
		}
		else
			i++;
	}
	if (q)
		return (1);
	return (exit);
}

int	count_words_quotes(char *s, int i, int count, int quote)
{
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
			count++;
		while (s[i] && s[i] != ' ')
		{
			if (s[i] == '"' || s[i] == 39)
			{
				quote = s[i];
				i++;
				while (s[i] && s[i] != quote)
					i++;
				if (s[i] == quote)
					i++;
			}
			else
				i++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (count);
}
