/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:40 by joopark           #+#    #+#             */
/*   Updated: 2021/02/24 13:45:45 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <libft.h>
# include <unistd.h>
# include <signal.h>
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
pid_t			ft_exec(char *file, char *argv[], char *envp[]);
int				ft_isexecutable(char *file);
char			*ft_find_exec(char *envp[], char *cmd);

// ft_getline.c
char			*ft_getline(char **bp);

// ft_env.c
char			*ft_getenv(char *envp[], char *key);

// ft_parser.c
char			**ft_parse_exec(char *cmd);
char			*ft_remove_quote(char *cmd);

// ft_string.c
char			*ft_strnstack(char *stack, char *str, size_t n);

// ft_exit.c
void			ft_exit(char *msg, int status);

#endif
