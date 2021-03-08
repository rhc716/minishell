/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:40 by joopark           #+#    #+#             */
/*   Updated: 2021/03/08 12:11:14 by joopark          ###   ########.fr       */
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

int				g_status;

char			*ft_getbuf(ssize_t clr, char **bp);
int				ft_prechk(int fd, char **line, char **bufrtn, char **bp);
int				ft_get_next_line(int fd, char **line, char **bp);
void			ft_signal(void);
void			ft_sigint(int code);
void			ft_sigkill(int code);
pid_t			ft_exec(char *file, char *argv[], char *envp[], int fd[]);
int				ft_isexecutable(char *file);
char			*ft_find_exec(char *envp[], char *cmd);
int				ft_exec_wait(pid_t *pids, int n);
char			*ft_getline(char **bp);
char			*ft_getenv(char *envp[], char *key);
char			**ft_setenv(char *envp[], char *key, char *value);
char			**ft_modenv(char *envp[], char *key, char *value);
char			**ft_newenv(char *envp[], char *key, char *value);
char			**ft_clearenv(char *envp[], char *key);
char			**ft_parse_split(char *str, char s, char c, char r);
char			*ft_parse_redirect(char *cmd, char **in, char **out, char *rp);
int				ft_parse_get_name(char *cmd, char **in, char **out, char *rp);
char			**ft_quote_remove_list(char **str);
char			*ft_parse_replace_quote(char *str, char c);
char			*ft_parse_replace_inquote(char *str, char c, char r);
char			*ft_strnstack(char *stack, char *str, size_t n);
char			**ft_strsdup(char *str[]);
void			ft_strsfree(char *str[]);
int				ft_getword(char *str, char **word);
char			*ft_strjoin_free(char *s1, char *s2, int free_case);
void			ft_exit(char *msg, int status);
int				ft_getfd(char *filename, char mode);
char			*ft_ext_iofd(char *cmd, int *i, int *o, int *err);
int				**ft_genpipes(int len);
int				ft_genpipe(int *i, int *o);
void			ft_closepipe(int **pipe, int len);
void			ft_run(char *cmd, char **envp[]);
void			ft_run_with_pipe(char *cmd, char **envp[]);
pid_t			ft_run_cmd(char *cmd, char **envp[], int io[]);
pid_t			ft_run_exec(char *args[], char **envp[], int io[]);
void			ft_prompt(void);
void			ft_loginmsg(char *file);
char			*ft_msgstr(char *file);
void			ft_ansi_escape(int i, int fd);
int				ft_check_builtins(char *cmd);
int				ft_exec_builtins(char **arg, char **envp[], int fd[]);
int				ft_cd(char **arg, char **envp[], int fd[]);
int				ft_echo(char **arg, char *envp[], int fd[]);
int				ft_env(char *envp[], int fd[]);
int				ft_export(char **arg, char **envp[], int fd[]);
int				ft_pwd(int fd[]);
int				ft_unset(char **arg, char **envp[], int fd[]);
int				ft_export_arg(char *key, char *val, char **envp[], int fd[]);
int				ft_isvalid_key(char *key);
void			ft_sort_2d_arr(char **arr);
int				ft_put_err_msg(char *s1, char *s2, char *s3, int fd);
void			ft_unset_str(char *str, char **envp[]);
char			*ft_replace_env_in_arg(char *arg, char *p
				, char *envp[], int free_yn);
#endif
