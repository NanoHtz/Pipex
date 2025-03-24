/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:16:38 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/02/26 11:16:38 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	free_and_exit(t_pipex *pipex, char **args, int code)
{
	free(pipex);
	free_array(args);
	exit(code);
}

void	free_array(char	**array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	execute(char *cmd, t_pipex *pipex, char **envp)
{
	char	**args;
	char	**path;
	char	*tmp;

	args = ft_split(cmd, ' ');
	if (!args[0])
		free_and_exit(pipex, args, 1);
	path = get_path(envp);
	tmp = NULL;
	tmp = search_correct_path(args[0], path);
	if (!tmp)
	{
		free_array(path);
		free_and_exit(pipex, args, 127);
	}
	execve(tmp, args, envp);
	free(tmp);
	free_array(args);
	free_array(path);
	exit(127);
}
