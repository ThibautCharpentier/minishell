/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:24:55 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/13 19:24:55 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*free_str_input(char *buf, char *save, int *pipefd, int error)
{
	if (buf)
		free(buf);
	if (save)
		free(save);
	close(pipefd[0]);
	free(pipefd);
	if (error == 1)
		free_all(1, "malloc");
	else if (error == 2)
		free_all(1, "read");
	return (NULL);
}

static char	*get_str_input(int *pipefd)
{
	char	*buf;
	int		nbr_oct;
	char	*save;

	buf = malloc(sizeof(char) * 2);
	if (!buf)
		free_all(1, "malloc");
	save = malloc(sizeof(char) * 1);
	if (!save)
		free_str_input(buf, save, pipefd, 1);
	save[0] = '\0';
	nbr_oct = 1;
	while (nbr_oct != 0)
	{
		nbr_oct = read(pipefd[0], buf, 1);
		if (nbr_oct < 0)
			free_str_input(buf, save, pipefd, 2);
		buf[nbr_oct] = '\0';
		save = ft_strjoin_free_s1(save, buf);
		if (!save)
			free_str_input(buf, save, pipefd, 1);
	}
	free_str_input(buf, NULL, pipefd, 0);
	return (save);
}

static void	read_redirection(char *limit, int *pipefd)
{
	char	*line;

	close(pipefd[0]);
	line = NULL;
	while (!ft_same_str(line, limit))
	{
		free(line);
		line = readline("> ");
		if (!line)
		{
			ft_putchar_fd('\n', 1);
			close(pipefd[1]);
			free(pipefd);
			exit(EXIT_SUCCESS);
		}
		if (!ft_same_str(line, limit))
		{
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
		}
	}
	free(line);
	close(pipefd[1]);
	free(pipefd);
	exit(EXIT_SUCCESS);
}

char	*get_redirection(char *limit)
{
	int	status;
	int	*pipefd;

	pipefd = malloc(sizeof(int) * 2);
	if (!pipefd)
		free_all(1, "malloc");
	if (pipe(pipefd) == -1)
		free_all(1, "pipe");
	g_var.redirection = 1;
	g_var.pid = fork();
	if (g_var.pid == -1)
		free_all(1, "fork");
	else if (g_var.pid == 0)
		read_redirection(limit, pipefd);
	if (wait(&status) < 0)
	{
		kill(g_var.pid, SIGTERM);
		free_all(1, "wait");
	}
	g_var.redirection = 0;
	g_var.pid = 0;
	close(pipefd[1]);
	if (WIFSIGNALED(status))
		return (free_str_input(NULL, NULL, pipefd, 0));
	return (get_str_input(pipefd));
}

void	get_line(void)
{
	if (g_var.line)
	{
		free(g_var.line);
		g_var.line = NULL;
	}
	while (!g_var.line)
	{
		g_var.line = readline("$> ");
		if (!g_var.line)
		{
			ft_putstr_fd("logout\n", 1);
			free_all(0, "");
		}
		if (ft_stronlyspace(g_var.line))
		{
			free(g_var.line);
			g_var.line = NULL;
		}
	}
	add_history(g_var.line);
}
