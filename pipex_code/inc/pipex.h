/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:55:37 by avalsang          #+#    #+#             */
/*   Updated: 2025/02/21 18:46:27 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

typedef struct s_list
{
	char			*path;
	char			**cmds;
	struct s_list	*next;
}				t_list;

typedef struct s_data
{
	int				in_fd;
	int				out_fd;
	int				error;
	int				last_cmd;
	int				last_pid;
	int				argc;
	int				here_doc;
	char			**env_paths;
	t_list			*cmd_list;
}		t_data;

// libft funcs
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	pipex_lstadd_back(t_list **lst, t_list *new);
char	*ft_strdup(const char *src);

// main
void	free_data(t_data *data);

// parse_cmds.c
void	get_envp_paths(t_data *data, char **envp);;
void	parse_cmds(int argc, char **argv, t_data *data);
char	*get_cmd_path(t_data *data, char *cmd);

// pipex_list_funcs.
t_list	*pipex_lstnew(char *path, char **cmds);
void	pipex_lstadd_back(t_list **lst, t_list *new);

// pipex_utils
void	init_struct(t_data *data, int argc);
void	open_infile(t_data *list, char **argv);
void	init_outfile(t_data *data, int argc, char **argv);
int		ft_strcmp(char *s1, char *s2);

// pipex_error
void	pipex_perror(void);
void	custom_error(char *str, char *msg, int errnum, t_data *data);

// free_pipex
void	free_array(char **arr);
void	free_data(t_data *data);

// gnl (bonus)
char	*get_next_line(int fd);

// here_doc (bonus)
void	here_doc(char *lim, t_data *data);

#endif
