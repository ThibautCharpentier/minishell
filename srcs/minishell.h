/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:01:43 by tcharpen          #+#    #+#             */
/*   Updated: 2022/05/09 14:01:45 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h" // contains unistd, stdarg, stdlib
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>

# define B_ECHO 0
# define B_CD 1
# define B_PWD 2
# define B_EXPORT 3
# define B_UNSET 4
# define B_ENV 5
# define B_EXIT 6

/* --------- STRUCT --------- */

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_com
{
	char				**command;
	int					fd_read;
	int					fd_write;
	char				*str_input;
	int					input;
	char				**limit;
	struct s_com		*next;
}				t_com;

typedef struct s_parsing
{
	char		**parse;
	char		*path;
	int			nbr_command;
}				t_parsing;

typedef struct s_minishell
{
	t_com		*lst_com;
	int			last_exit;
	char		**builtins;
	char		**path;
	t_env		*lst_env;
	int			**pipe;
	int			nb_pipe;
	int			pipe_idx;
	char		*line;
	pid_t		pid;
	t_parsing	parsing;
	int			redirection;
}				t_minishell;

extern t_minishell	g_var;

/* --------- FCT --------- */

/* builtins */
void	run_echo(t_com *lst_com);
void	run_cd(t_com *lst_com);
char	*check_directory(char *path, int *b_free);
void	run_export(t_com *lst_com);
void	print_export(t_com *lst_com);
void	run_pwd(t_com *lst_com);
void	run_unset(t_com *lst_com);
void	run_env(t_com *lst_com);
void	run_exit(t_com *lst_com);

/* execution */
void	execution(void);
void	init_pipe(void);
int		check_builtins(char *command);
void	run_builtin(t_com *lst_com, int builtin);
int		run_path(t_com *lst_com);
void	run_file(t_com *lst_com, char *path);
void	run_command(char *path, t_com *lst_com);
void	run_fork(char *path, t_com *lst_com);

/* init */
void	init(char **env);
char	**init_builtins(void);
char	**init_path(t_env *lst_env, int init);
t_env	*init_env(char **env);

/* parsing */
t_com	*init_command(int nbr_command);
int		parse(char *line);
int		count_quote(char *line);
int		find_pair(char *str, char pair, int *i);
int		variable_env(char *line, int *i);
void	get_line(void);
char	*get_redirection(char *limit);
int		is_space(char c);
int		separate_by_pipe(char *line);
void	skip_quote(char *line, char c, int *i);
int		strlen_c(char *line, char c);
void	put_variable(char **parse);
char	*remalloc_without(char *parse, int *index, int size_delete);
char	*remalloc_lastexit(char *parse, int *index);
char	*remalloc_with_var(char *parse, char *var, char *value, int *index);
int		redirect(char **parse);
int		check_redirect(char **parse);
int		size_word(char *line, int space);
int		malloc_path(char *parse, int type, t_com *lst_com);
int		open_path(char *path, int type, t_com *lst_com);
void	free_doubletab(char **tabstr);
char	*free_under_tab(char *under_tab);
void	command_tab(char **parse, t_com *lst_com, int nbr_command);
void	wtf_readline(void);
char	**malloc_limit(char *path, t_com *lst_com);
int		size_path(char *line, int space);

/* utils */
char	*ft_strprechr(char *str, char c);
char	*ft_strpostchr(char *str, char c);
int		ft_stronlyspace(char *str);
int		ft_same_str(char *s1, char *s2);
int		what_fd(t_com *lst_com);
char	*get_env(char *the_key);
int		set_env(char *key, char *value);
int		ft_strcmp(const char *s1, const char *s2);
char	*malloc_string_env(t_env *lst_env, char **env);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	*ft_itoa(int nbr);
char	*ft_add_str_in_chain(char *new, char *chain, char *str, int index);
char	*ft_complete_chain(char *new, char *chain, int index_new);

/* error */
int		path_error(char *str, char *path);
int		syntax_error(char *str);
void	malloc_error(void);
int		print_command_error(char *str);

/* free */
void	free_lst_env(t_env *lst, int error);
void	free_lst_com(t_com *lst);
void	free_tabstr(char **tabstr, int error);
void	free_all(int error, char *str_error);
void	free_pipe(int **pipe);

/* signal */
void	signal_received(int sig);
void	remove_signal(void);
void	finish_process(int sig);
void	init_signal(void);

#endif
