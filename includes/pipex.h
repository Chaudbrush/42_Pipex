/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:40:17 by vloureir          #+#    #+#             */
/*   Updated: 2025/06/26 18:27:13 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXEC_FAIL 127

typedef struct s_cmd
{
	pid_t			pid;
	char			*path;
	char			**cmds;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	int		status;
	int		opened_fds[2];
	int		pipe_fds[2];
	t_cmd	*cmd_lst;
}			t_data;

// Main
void	first_child(t_data *data);
void	second_child(t_data *data);

// Data Init
char	*no_env(char *cmd);
int		get_index(t_data *data);
void	get_commands(t_data *data);
char	**organize_env(char **envp);
char	*get_correct_path(char **cmds, char **envp);

// Parse
char	*check_access(char **args);
int		open_files(t_data *data, int argc, char **argv);
void	parse_input(int argc, char **argv, char **envp);
void	ft_init_data(t_data *data, int argc, char **argv, char **envp);

// Free and Exit
void	free_lst(t_cmd *lst);
void	ft_close_fds(int *fds);
void	free_array(char **array);
int		free_and_exit(t_data *data, char *str, int flag);

// Libft
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	**ft_split(char *str, char c);
char	**env_split(char *str, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
