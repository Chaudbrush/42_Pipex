/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:35:51 by vloureir          #+#    #+#             */
/*   Updated: 2025/06/24 21:58:48 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**organize_env(char **envp)
{
	int		i;
	int		j;

	if (envp[0] == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			while (envp[i][++j] != '=')
				j++;
			j++;
			return (env_split(&envp[i][j], ':'));
		}
	}
	return (NULL);
}

char	*check_access(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (access(args[i], X_OK) == 0)
			return (args[i]);
	}
	return (NULL);
}

int	get_index(t_data *data)
{
	if (ft_strncmp(data->argv[1], "here_doc", 9) == 0)
		return (3);
	else
		return (2);
}

char	*get_correct_path(char **cmds, char **envp)
{
	int		i;
	char	*tmp;

	if (cmds == NULL || cmds[0] == NULL)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		tmp = ft_strjoin(envp[i], cmds[0]);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (ft_strdup(cmds[0]));
}

void	get_commands(t_data *data)
{
	int		i;
	t_cmd	*node;

	i = 3;
	while (i > 1)
	{
		node = malloc(sizeof(t_cmd));
		if (node == NULL)
			free_and_exit(data, "Malloc", 1);
		node->cmds = ft_split(data->argv[i], ' ');
		node->path = get_correct_path(node->cmds, data->envp);
		node->next = data->cmd_lst;
		data->cmd_lst = node;
		i--;
	}
}
