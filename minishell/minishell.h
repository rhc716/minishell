/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:40 by joopark           #+#    #+#             */
/*   Updated: 2021/02/26 14:30:12 by joopark          ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

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

// ft_getline.c
char			*ft_getline(char **bp);

// ft_envctrl.c
char			*ft_getenv(char *envp[], char *key);
char			**ft_setenv(char *envp[], char *key, char *value);
char			**ft_modenv(char *envp[], char *key, char *value);
char			**ft_newenv(char *envp[], char *key, char *value);
char			**ft_clearenv(char *envp[], char *key);

// ft_parser.c
char			*ft_parse_replace_quote(char *str, char c);
char			*ft_parse_replace_inquote(char *str, char c, char r);
char			**ft_parse_split(char *str, char s, char c, char r);
char			*ft_parse_redirect(char *cmd, char **in, char **out, char *rp);

// ft_string.c
char			*ft_strnstack(char *stack, char *str, size_t n);
char			**ft_strsdup(char *str[]);
void			ft_strsfree(char *str[]);
int				ft_getword(char *str, char **word);

// ft_exit.c
void			ft_exit(char *msg, int status);

// ft_ioctl.c
int				ft_getfd(char *filename, char mode);

// ft_builtins.c
int				ft_check_builtins(char *cmd);
int				ft_exec_builtins(char **arg, char **envp[]);

// builtins
void			ft_cd(char **arg, char *envp[]);
void			ft_echo(char **arg, char *envp[]);
void			ft_env(char *envp[]);
void			ft_export(char **arg, char **envp[]);
void			ft_pwd(void);
void			ft_unset(char **arg, char **envp[]);

// ft_export.c
void			ft_export_arg(char *key, char *val, char **envp[]);

#endif
