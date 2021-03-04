/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:40 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 13:47:21 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <libft.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct	s_com
{
	int			status;
}				t_com;

// ft_get_next_line.c
char			*ft_getbuf(ssize_t clr, char **bp);
int				ft_prechk(int fd, char **line, char **bufrtn, char **bp);
int				ft_get_next_line(int fd, char **line, char **bp);

// ft_signal.c
void			ft_signal(void);
void			ft_sigint(int code);
void			ft_sigkill(int code);

// ft_exec.c
pid_t			ft_exec(char *file, char *argv[], char *envp[], int fd[]);
int				ft_isexecutable(char *file);
char			*ft_find_exec(char *envp[], char *cmd);
int				ft_exec_wait(pid_t *pids, int n);

// ft_getline.c
char			*ft_getline(char **bp);

// ft_envctrl.c
char			*ft_getenv(char *envp[], char *key);
char			**ft_setenv(char *envp[], char *key, char *value);
char			**ft_modenv(char *envp[], char *key, char *value);
char			**ft_newenv(char *envp[], char *key, char *value);
char			**ft_clearenv(char *envp[], char *key);

// ft_parser.c
char			**ft_parse_split(char *str, char s, char c, char r);
char			*ft_parse_redirect(char *cmd, char **in, char **out, char *rp);
int				ft_parse_get_name(char *cmd, char **in, char **out, char *rp);

// ft_quote.c
char			*ft_quote_remove(char *str);
char			*ft_parse_replace_quote(char *str, char c);
char			*ft_parse_replace_inquote(char *str, char c, char r);

// ft_string.c
char			*ft_strnstack(char *stack, char *str, size_t n);
char			**ft_strsdup(char *str[]);
void			ft_strsfree(char *str[]);
int				ft_getword(char *str, char **word);
char			*ft_strjoin_free(char *s1, char *s2, int free_case);

// ft_exit.c
void			ft_exit(char *msg, int status);

// ft_ioctrl.c
int				ft_getfd(char *filename, char mode);
char			*ft_ext_iofd(char *cmd, int *i, int *o, int *err);
int				**ft_genpipes(int len);
int				ft_genpipe(int *i, int *o);
void			ft_closepipe(int **pipe, int len);

// ft_run.c
void			ft_run(char *cmd, char **envp[], t_com *com);
void			ft_run_with_pipe(char *cmd, char **envp[], t_com *com);
pid_t			ft_run_cmd(char *cmd, char **envp[], int io[], t_com *com);
pid_t			ft_run_exec(char *args[], char **envp[], int io[], t_com *com);

// ft_console.c
void			ft_prompt(void);
void			ft_loginmsg(char *file);
char			*ft_msgstr(char *file);
void			ft_ansi_escape(int i);

// ft_builtins.c
int				ft_check_builtins(char *cmd);
void			ft_exec_builtins(char **arg, char **envp[], int fd[], t_com *com);

// builtins
int				ft_cd(char **arg, char **envp[], int fd[]);
int				ft_echo(char **arg, char *envp[], int fd[], t_com *com);
int				ft_env(char *envp[], int fd[]);
int				ft_export(char **arg, char **envp[], int fd[]);
int				ft_pwd(int fd[]);
int				ft_unset(char **arg, char **envp[], int fd[]);

// ft_export.c
int				ft_export_arg(char *key, char *val, char **envp[], int fd[]);
int				ft_isvalid_key(char *key);

// ft_builtins_util.c
void			ft_sort_2d_arr(char **arr);
void			ft_put_err_msg(char *s1, char *s2, char *s3, int fd);
#endif
