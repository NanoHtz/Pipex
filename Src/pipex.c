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
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

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

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	int		infile;
	int		outfile;
	pid_t	pid;
	char	*cmd_path;
	char	**cmd_args;

	if (ac != 5)
		ft_error(ARGS_ERROR);
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		ft_error(OPEN_ERROR);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		close(infile);
		ft_error(OPEN_ERROR);
	}
	if (pipe(fd) == -1)
		ft_error(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
		ft_error(FORK_ERROR);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(infile);
		close(outfile);
		cmd_path = find_command_path(av[2], envp);
		if (!cmd_path)
			ft_error(COMMAND_NOT_FOUND);
		cmd_args = ft_split(av[2], ' ');
		if (!cmd_args)
		{
			free(cmd_path);
			ft_error(MEMORY_ERROR);
		}
		execve(cmd_path, cmd_args, envp);
		ft_free_split(cmd_args);
		free(cmd_path);
		ft_error(EXECVE_ERROR);
	}
	if (pid > 0)
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(fd[0]);
		close(outfile);
		close(infile);
		cmd_path = find_command_path(av[3], envp);
		if (!cmd_path)
			ft_error(COMMAND_NOT_FOUND);
		cmd_args = ft_split(av[3], ' ');
		if (!cmd_args)
		{
			free(cmd_path);
			ft_error(MEMORY_ERROR);
		}
		execve(cmd_path, cmd_args, envp);
		ft_free_split(cmd_args);
		free(cmd_path);
		ft_error(EXECVE_ERROR);
	}
	return (0);
}
