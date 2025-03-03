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

t_files	*ft_open(char **av)
{
	t_files	*files;

	files = (t_files *)malloc(sizeof(t_files));
	if (!files)
		ft_error(MALLOC_ERROR);
	files->infile = open(av[1], O_RDONLY, 0777);
	if (files->infile == -1)
	{
		free(files);
		ft_error(OPEN_ERROR_INFILE);
	}
	files->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (files->outfile == -1)
	{
		free(files);
		ft_error(OPEN_ERROR_OUTFILE);
	}
	return (files);
}

void	execute_command(char *av, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	path = find_command_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		ft_free_split(cmd);
		ft_error(COMMAND_ERROR);
	}
}

void	parent_process(int fd[], char **envp, char **av, t_files *files)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(files->outfile, STDOUT_FILENO);
	close(fd[1]);
	execute_command(av[3], envp);
}

void	child_process(int fd[], char **envp, char **av, t_files *files)
{
	dup2(fd[1], STDOUT_FILENO);
	dup2(files->infile, STDIN_FILENO);
	close(fd[0]);
	execute_command(av[2], envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		fd[2];
	t_files	*files;

	if (ac == 5)
	{
		files = ft_open(av);
		if (pipe(fd) == -1)
			ft_error(PIPE_ERROR);
		pid = fork();
		if (pid < 0)
			ft_error(FORK_ERROR);
		else if (pid == 0)
			child_process(fd, envp, av, files);
		else
		{
			waitpid(pid, NULL, 0);
			parent_process(fd, envp, av, files);
		}
	}
	else
		ft_error(ARGS_ERROR);
	return (0);
}
