/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:56:19 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/03/22 15:56:19 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	parent_process(t_pipex	*pipex, char **av, char **envp)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
	{
		free(pipex);
		ft_error(OPEN_ERROR_OUTFILE);
	}
	dup2(outfile, 1);
	close(outfile);
	dup2(pipex->fd[0], 0);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execute(av[3], pipex, envp);
}

void	child_process(t_pipex	*pipex, char **av, char **envp)
{
	int	infile;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile < 0)
	{
		free(pipex);
		ft_error(OPEN_ERROR_INFILE);
	}
	dup2(infile, 0);
	close(infile);
	dup2(pipex->fd[1], 1);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	execute(av[2], pipex, envp);
}

void	fork_process(t_pipex *pipex, char **av, char **envp)
{
	pipex->pid[0] = fork();
	if (pipex->pid[0] < 0)
	{
		free(pipex);
		ft_error(FORK_ERROR);
	}
	if (pipex->pid[0] == 0)
		child_process(pipex, av, envp);
	pipex->pid[1] = fork();
	if (pipex->pid[1] < 0)
	{
		free(pipex);
		ft_error(FORK_ERROR);
	}
	if (pipex->pid[1] == 0)
		parent_process(pipex, av, envp);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

void	create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->fd) == -1)
	{
		free(pipex);
		ft_error(PIPE_ERROR);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;
	int		status[2];

	if (ac != 5)
		ft_error(ARGS_ERROR);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		ft_error(MALLOC_ERROR);
	create_pipe(pipex);
	fork_process(pipex, av, envp);
	waitpid(pipex->pid[0], &status[0], 0);
	waitpid(pipex->pid[1], &status[1], 0);
	free(pipex);
	return (status[1] >> 8);
}
