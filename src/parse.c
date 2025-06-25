/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:48:06 by vloureir          #+#    #+#             */
/*   Updated: 2025/06/25 11:13:42 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parse_input(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	if (argc != 5)
	{
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		exit (EXIT_FAILURE);
	}
}

void	ft_init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = organize_env(envp);
	data->cmd_lst = NULL;
	open_files(data, argc, argv);
	get_commands(data);
}

int	open_files(t_data *data, int argc, char **argv)
{
	char	*file_1;
	char	*file_2;

	(void)argc;
	file_1 = argv[1];
	file_2 = argv[4];
	data->opened_fds[0] = open(file_1, O_RDONLY);
	if (data->opened_fds[0] == -1)
		perror(argv[1]);
	data->opened_fds[1] = open(file_2, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->opened_fds[1] == -1)
		perror(argv[4]);
	return (0);
}
