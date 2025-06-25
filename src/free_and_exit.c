/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:51:19 by vloureir          #+#    #+#             */
/*   Updated: 2025/06/25 11:00:06 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_lst(t_cmd *lst)
{
	t_cmd	*ptr;

	ptr = lst;
	while (ptr)
	{
		lst = lst->next;
		free(ptr->path);
		free_array(ptr->cmds);
		free(ptr);
		ptr = lst;
	}
}

int	free_and_exit(t_data *data, char *str, int flag)
{
	if (str)
		perror(str);
	if (data->envp)
		free_array(data->envp);
	free_lst(data->cmd_lst);
	ft_close_fds(data->opened_fds);
	ft_close_fds(data->pipe_fds);
	exit(flag);
}

void	ft_close_fds(int *fds)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (fds[i] > 2)
			close(fds[i]);
		i++;
	}
}