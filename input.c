/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:47 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/18 12:51:57 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_replace_with_content(char *line, char *cont, int st, int end)
{
	char	*new;
	int		i;

	i = 0;
	if (cont)
		new = ft_calloc(sizeof(char),
				ft_strlen(line) - (end - st) + ft_strlen(cont) + 1);
	else
		new = ft_calloc(sizeof(char), ft_strlen(line) - (end - st) + 1);
	while (i < st)
	{
		new[i] = line[i];
		i++;
	}
	if (cont)
	{
		new[i] = '\0';
		ft_joininplace(&new, cont);
		free(cont);
		i = ft_strlen(new);
	}
	ft_joininplace(&new, line + end);
	free(line);
	return (new);
}

static char	*ft_replace_name(char *line, int start, int end)
{
	char	*content;
	char	*name;
	int		i;

	name = ft_calloc(sizeof(char), end - start);
	i = 0;
	while (start + i + 1 < end)
	{
		name[i] = line[start + 1 + i];
		i++;
	}
	name[i] = '\0';
	if (name[0] != '?')
		content = ft_getenv(name);
	else
		content = ft_itoa(g_global.return_code);
	free(name);
	line = ft_replace_with_content(line, content, start, end);
	return (line);
}

char	*ft_replace_envvariable(char *line)
{
	int		end;
	t_env	e;

	e = (t_env){0};
	while (line[e.start])
	{
		if (line[e.start] == '$' && e.singleq % 2 == 0)
			break ;
		else if (line[e.start] == '"')
			e.doubleq++;
		else if (line[e.start] == '\'' && e.doubleq % 2 == 0)
			e.singleq++;
		e.start++;
	}
	end = e.start + 1;
	if (line[end] && line[end] == '?')
		end++;
	else
	{
		while (line[end] && (ft_isalnum(line[end]) || line[end] == '_'))
			end++;
	}
	line = ft_replace_name(line, e.start, end);
	return (line);
}

t_list	*input_list(char *line)
{
	char	**tab;
	t_list	*begin_list;
	int		i;

	tab = get_tab(line);
	if (tab == NULL)
		return (NULL);
	begin_list = NULL;
	ft_lstadd_back(&begin_list, tab[0]);
	i = 1;
	while (tab[i])
	{
		ft_lstadd_back(&begin_list, remove_quotes(tab[i]));
		i++;
	}
	ft_free_2darray(tab);
	return (begin_list);
}
