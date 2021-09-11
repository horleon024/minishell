/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 22:31:15 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/05 22:31:16 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strdel(char *str, int i)
{
	char	*new;
	int		j;

	new = malloc(sizeof(char) * ft_strlen(str));
	j = 0;
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	while (j < (int)ft_strlen(str) - 1)
	{
		new[j] = str[j + 1];
		j++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

/* function to join everything after first 
parameter (from quotes split) to strs[0]; */

char	*join_str_space(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	i = 0;
	j = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = ' ';
	i++;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	free(s1);
	return (new);
}

void	join_redirect(char **strs)
{
	char	**tab;
	int		i;

	tab = ft_split_quotes(strs[1]);
	i = 1;
	while (tab[i])
	{
		strs[0] = join_str_space(strs[0], tab[i]);
		i++;
	}
}

void	redirect_main(char *line)
{
	char	**strs;
	int		*fd;

	strs = NULL;
	fd = malloc(2 * sizeof(int));
	if (contains_redirect(line) == -1)
	{
		printf("Invalid command syntax\n");
		return ;
	}
	if (contains_redirect(line) == 1)
		fredirect_single(line, 0, strs);
	else if (contains_redirect(line) == 2)
		fredirect_double(line, 0, strs);
	else if (contains_redirect(line) == 3)
		bredirect_single(line, 0, strs, fd);
	else if (contains_redirect(line) == 4)
		bredirect_double(line, 0, strs);
}
