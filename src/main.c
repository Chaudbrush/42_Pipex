/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:37:57 by vloureir          #+#    #+#             */
/*   Updated: 2025/06/25 11:16:54 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	t_data	data;

	parse_input(argc, argv, envp);
	if (pipe(data.pipe_fds) == -1)
		free_and_exit(&data, "Pipe", EXIT_FAILURE);
	ft_init_data(&data, argc, argv, envp);
	pid1 = fork();
	if (pid1 == -1)
		free_and_exit(&data, "Fork", EXIT_FAILURE);
	if (pid1 == 0)
		first_child(&data);
	pid2 = fork();
	if (pid2 == -1)
		free_and_exit(&data, "Fork", EXIT_FAILURE);
	if (pid2 == 0)
		second_child(&data);
	ft_close_fds(data.pipe_fds);
	waitpid(pid1, &data.status, 0);
	waitpid(pid2, &data.status, 0);
	free_and_exit(&data, NULL, WEXITSTATUS(data.status));
}

void	first_child(t_data *data)
{
	t_cmd	*ptr;

	ptr = data->cmd_lst;
//	data->opened_fds[0] = open(data->argv[1], O_RDONLY);
	if (dup2(data->opened_fds[0], STDIN_FILENO) == -1)
		free_and_exit(data, "Dup2", EXIT_FAILURE);
	ft_close_fds(data->opened_fds);
	if (dup2(data->pipe_fds[1], STDOUT_FILENO) == -1)
		free_and_exit(data, "Dup2", EXIT_FAILURE);
	ft_close_fds(data->pipe_fds);
//	write(2, "antes do execve\n", 16); // Delete this
	execve(ptr->path, ptr->cmds, data->envp);
//	write(2, "depois do execve\n", 17); // Delete this
	ft_putstr_fd(data->argv[2], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_and_exit(data, NULL, EXEC_FAIL);
}

void	second_child(t_data *data)
{
	t_cmd	*ptr;

	ptr = data->cmd_lst->next;
//	data->opened_fds[1] = open(data->argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (dup2(data->opened_fds[1], STDOUT_FILENO) == -1)
		free_and_exit(data, "Dup2", EXIT_FAILURE);
	ft_close_fds(data->opened_fds);
	if (dup2(data->pipe_fds[0], STDIN_FILENO) == -1)
		free_and_exit(data, "Dup2", EXIT_FAILURE);
	ft_close_fds(data->pipe_fds);
//	write(2, "antes do execve\n", 16); // Delete this
	execve(ptr->path, ptr->cmds, data->envp);
//	write(2, "depois do execve\n", 17); // Delete this
	ft_putstr_fd(data->argv[3], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_and_exit(data, NULL, EXEC_FAIL);
}
