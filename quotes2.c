/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 22:31:29 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/05 22:31:30 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Counts size until next space, ignoring spaces within quotes */
int	size_ahead_quotes(char *s, int i)
{
	int		j;
	int		quote;
	char	q;

	j = 0;
	quote = 0;
	while (s[i + j] && (s[i + j] != ' ' || quote))
	{
		if ((s[i + j] == '"' || s[i + j] == 39) && !quote)
		{
			quote = 1;
			q = s[i + j];
		}
		else if (s[i + j] == q)
			quote = 0;
		j++;
	}
	return (j);
}

char	*ft_strcpy_quotes(char *s, int i, int size, char *tab)
{
	int	j;

	j = 0;
	tab = malloc(sizeof(char) * (size + 1));
	if (tab == NULL)
		return (NULL);
	while (j < size && s[i + j] != '\0')
	{
		tab[j] = s[i + j];
		j++;
	}
	tab[j] = '\0';
	return (tab);
}

char	**assign_quotes(char *s, char **tab, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < count)
	{
		while (s[i] == ' ')
			i++;
		tab[j] = ft_strcpy_quotes(s, i, size_ahead_quotes(s, i), tab[j]);
		if (!tab[j])
		{
			while (j >= 0)
			{
				free(tab[j]);
				j--;
			}
			free(tab);
			return (NULL);
		}
		i += ft_strlen(tab[j]);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_quotes(char *s)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = count_words_quotes(s, 0, 0, 0);
	tab = malloc((count + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = assign_quotes(s, tab, count);
	return (tab);
}

char	**get_tab(char *line)
{
	if (!(count_quotes(line, 0, 0, 0)))
		return (ft_split(line, ' '));
	else if (count_quotes(line, 0, 0, 0) == 1)
	{
		printf("Invalid command syntax: unclosed quotes\n");
		return (NULL);
	}
	else
		return (ft_split_quotes(line));
}
