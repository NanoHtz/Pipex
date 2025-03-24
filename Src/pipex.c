/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:18:11 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/02/17 14:18:11 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

char	*search_correct_path(char *cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	**get_path(char **envp)
{
	int		i;
	char	*path;
	char	**dir;
	char	*tmp;

	i = 0;
	path = NULL;
	while (envp[i++])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			break ;
		}
	}
	dir = ft_split(path, ':');
	free(path);
	i = -1;
	while (dir[++i])
	{
		tmp = ft_strjoin(dir[i], "/");
		free(dir[i]);
		dir[i] = tmp;
	}
	return (dir);
}
