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

char	*is_executable(char *cmd_path, char **paths)
{
	if (access(cmd_path, X_OK) == 0)
	{
		ft_free_split(paths);
		return (cmd_path);
	}
	free(cmd_path);
	return (NULL);
}

char	**get_paths(char **envp)
{
	char	*path;
	char	**paths;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!*envp)
		return (NULL);
	path = *envp + 5;
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	char	*temp;
	int		i;

	paths = get_paths(envp);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_split(paths), NULL);
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!cmd_path)
			return (ft_free_split(paths), NULL);
		if (is_executable(cmd_path, paths))
			return (cmd_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}
