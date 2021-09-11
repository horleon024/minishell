/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:30 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/18 13:45:54 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

# ifdef __linux__
#  include <readline/readline.h>
#  include <readline/history.h>
# elif __APPLE__
char	*readline(const char *prompt);
int		add_history(const char *string_for_history);
int		rl_on_new_line(void);
void	rl_redisplay(void);
void	rl_replace_line(const char *buffer, int something);
# endif

# define PATH_MAX 4096

typedef struct s_global
{
	char	**env;
	int		return_code;
	int		pid;
}			t_global;

typedef struct s_env
{
	int	start;
	int	singleq;
	int	doubleq;
}		t_env;

t_global	g_global;

int		ft_pwd(void);
void	ft_exec_command(char *line);
int		cd(t_list *input);
t_list	*input_list(char *line);
int		get_arraylength(char **arr);
void	handle_sigint(int sig);
void	minishell(void);
char	*ft_getenv(char *str);
void	ft_joininplace(char **str, char *str2);
void	ft_load_history(void);
void	ft_add_history(char *line);
bool	ft_is_delimeter(char *str);
char	*ft_get_last_content(char *line);
int		ft_isspace(char *str);
char	**strpipefeed(char **strs, char *s, int i);
char	**split_pipe(char *line, char quote, char q);
void	pipe_main(char *s);
void	ft_update_env(char *var, char *new);
int		ft_env(void);
int		ft_export(t_list *input);
int		contains_and(char *str);
void	sc_section(char *line);
void	split_operator(char *line);
int		echo(t_list *input, int n);
bool	ft_variable_is_valid(char *str);
int		ft_unset(t_list *input);
bool	ft_contains_char(char *str, char c);
char	**ft_get_paths(void);
char	*ft_getcwd(void);
void	ft_free_2darray(char **strs);
int		ft_args_length(t_list *input);
void	redirect_main(char *line);
void	fredirect_single(char *line, int pid, char **strs);
void	bredirect_single(char *line, int pid, char **strs, int *fd);
void	bredirect_double(char *line, int pid, char **strs);
void	fredirect_double(char *line, int pid, char **strs);
char	**split_redirect(int n, char *line);
int		contains_redirect(char *line);
char	**get_tab(char *line);
char	**ft_split_quotes(char *s);
char	**assign_quotes(char *s, char **tab, int count);
char	*ft_strcpy_quotes(char *s, int i, int size, char *tab);
int		size_ahead_quotes(char *s, int i);
int		count_words_quotes(char *s, int i, int count, int quote);
int		count_quotes(char *line, int sing, int doub, int exit);
void	change_quote_status(int *q, int *exit, int *i);
char	*remove_quotes(char *line);
char	*ft_strdel(char *str, int i);
int		outer_quote(char *line);
int		contains_pipe(char *line);
void	join_redirect(char **strs);
char	*join_str_space(char *s1, char *s2);
void	ft_lst_env_change(t_list *lst);
void	ft_free_list(t_list *lst);
void	ft_exit(t_list *input, char *line);
char	*ft_replace_envvariable(char *line);

#endif