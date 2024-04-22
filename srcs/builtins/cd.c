/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:44:35 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/21 15:44:35 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_cwd(char *path, char *pwd)
{
	int		error;

	error = 0;
	if (chdir(path))
		error = 2;
	else
	{
		if (!set_env("OLDPWD", pwd))
			error = 3;
		free(pwd);
		if (error == 0)
		{
			pwd = getcwd(NULL, 0);
			if (!pwd)
				error = 1;
			else if (!set_env("PWD", pwd))
				error = 3;
			free(pwd);
		}
	}
	if (error == 2)
		free(pwd);
	return (error);
}

static void	change_directory(char *path, int *bool_malloc)
{
	char	*pwd;
	int		error;

	if (g_var.nb_pipe > 0)
	{
		if (*bool_malloc == 1)
			free(path);
		g_var.last_exit = 0;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
		error = change_cwd(path, pwd);
	else
		error = 1;
	if (*bool_malloc == 1)
		free(path);
	if (error == 1)
		free_all(1, "getcwd");
	if (error == 2)
		free_all(1, "chdir");
	if (error == 3)
		free_all(1, "malloc");
	g_var.last_exit = 0;
}

static char	*check_conditions(char *path, t_com *lst_com, int *bool_malloc)
{
	char	*str;

	if (!path)
		return (NULL);
	if (ft_same_str(path, "-"))
	{
		path = get_env("OLDPWD");
		if (!path)
		{
			print_command_error("cd: OLDPWD not set\n");
			return (NULL);
		}
		ft_putstr_fd(path, what_fd(lst_com));
		ft_putchar_fd('\n', what_fd(lst_com));
	}
	str = check_directory(path, bool_malloc);
	if (!str)
		return (path);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(str, 2);
	free(str);
	if (*bool_malloc == 1)
		free(path);
	return (NULL);
}

static char	*get_path(char *arg, int *bool_malloc)
{
	char	*home;
	char	*tmp;

	if (!ft_strncmp(arg, "~/", 2))
	{
		home = get_env("HOME");
		if (!home)
		{
			print_command_error("cd: HOME not set\n");
			return (NULL);
		}
		if (home[ft_strlen(home) - 1] != '/')
			tmp = ft_substr(arg, 1, ft_strlen(arg));
		else
			tmp = ft_substr(arg, 2, ft_strlen(arg));
		if (!tmp)
			free_all(1, "malloc");
		arg = ft_strjoin(home, tmp);
		free(tmp);
		if (!arg)
			free_all(1, "malloc");
		*bool_malloc = 1;
	}
	return (arg);
}

void	run_cd(t_com *lst_com)
{
	char	*path;
	int		bool_malloc;

	bool_malloc = 0;
	g_var.last_exit = 1;
	if (lst_com->command[1] && lst_com->command[2])
	{
		print_command_error("cd: too many arguments\n");
		return ;
	}
	else if (!lst_com->command[1] || ft_same_str(lst_com->command[1], "~")
		|| ft_same_str(lst_com->command[1], "--"))
	{
		path = get_env("HOME");
		if (!path)
		{
			print_command_error("cd: HOME not set\n");
			return ;
		}
	}
	else
		path = get_path(lst_com->command[1], &bool_malloc);
	path = check_conditions(path, lst_com, &bool_malloc);
	if (path)
		change_directory(path, &bool_malloc);
}
