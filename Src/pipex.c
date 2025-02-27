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

void	execute_command(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = find_command_path(cmd, envp);
	if (!cmd_path)
		ft_error(COMMAND_NOT_FOUND);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
	{
		free(cmd_path);
		ft_error(MEMORY_ERROR);
	}
	execve(cmd_path, cmd_args, envp);
	ft_free_split(cmd_args);
	free(cmd_path);
	ft_error(EXECVE_ERROR);
	execute_command(cmd, envp);
}

void	parent_process(int fd[], char **envp, char **av)
{
	int		outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		ft_error(OPEN_ERROR_OUTFILE);
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute_command(av[3], envp);
}

void	child_process(int fd[], char **envp, char **av)
{
	int		infile;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		ft_error(OPEN_ERROR_INFILE);
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute_command(av[2], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			ft_error(PIPE_ERROR);
		pid = fork();
		if (pid == -1)
			ft_error(FORK_ERROR);
		if (pid == 0)
			child_process(fd, envp, av);
		wait(NULL);
		parent_process(fd, envp, av);
	}
	else
		ft_error(ARGS_ERROR);
	return (0);
}
