/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:23 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/18 12:49:41 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_list *input)
{
	if (input->next && chdir(input->next->content))
		ft_putendl_fd("Wrong path", 2);
	else if (!input->next)
		chdir("/");
	g_global.return_code = 0;
	return (0);
}

int	echo(t_list *input, int n)
{
	while (input->next)
	{
		input = input->next;
		printf("%s", input->content);
		if (input->next)
			printf(" ");
	}
	if (n == 0)
		printf("\n");
	g_global.return_code = 0;
	return (0);
}

static bool	ft_is_numeric(char *str)
{
	int	 i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	ft_check_arguments(t_list *input)
{
	int	ret;

	ret = -1;
	while (input)
	{
		if (!ft_is_numeric(input->content))
			printf("minishell: exit: %s: numeric argument required\n",
				input->content);
		else if (ret == -1)
			ret = ft_atoi(input->content);
		else
		{
			printf("minishell: exit: too many arguments\n");
			return (-2);
		}
		input = input->next;
	}
	return (ret);
}

void	ft_exit(t_list *input, char *line)
{
	int	ret;

	printf("exit\n");
	input = input->next;
	ret = ft_check_arguments(input);
	if (ret != -2)
	{
		ft_free_list(input);
		free(line);
		ft_free_2darray(g_global.env);
	}
	if (ret == -1)
		exit(EXIT_SUCCESS);
	else if (ret >= 0)
		exit(ret);
}
