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

t_files	ft_open(int fd[], char **av)
{
	t_files files;

	files->infile = open(av[1], O_RDONLY, 0777);
	if (files->infile == -1)
	{
		ft_error(OPEN_ERROR_INFILE);
		exit(EXIT_FAILURE);
	}
	files->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (files->outfile == -1)
	{
		ft_error(OPEN_ERROR_OUTFILE);
		exit(EXIT_FAILURE);
	}
	return files
}

void	execute_command(char *av, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(av, ' ');
	path = find_command_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		ft_error("error");
	}
	if (execve(path, cmd, envp) == -1)
		ft_error("error");
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
	pid_t	pid;
	int		fd[2];
	t_files	files;

	if (ac == 5)
	{
		files = ft_open(fd, av);
		if (pipe(fd) == -1)
			ft_error(PIPE_ERROR);
		pid = fork();
		if (pid == -1)
			ft_error(FORK_ERROR);
		else if (pid == 0)
			child_process(fd, envp, av);
		else
		{
			waitpid(pid, NULL, 0);
			parent_process(fd, envp, av);
		}
	}
	else
		ft_error(ARGS_ERROR);
	return (0);
}
