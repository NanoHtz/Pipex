/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:18:23 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/02/17 14:18:23 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> //Para pruebas, borrar si es necesario
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "utils/errors.h"
# include "libft/libft.h"

typedef struct s_pipex
{
	pid_t	pid[2];
	int		fd[2];
	char	**av;
}	t_pipex;

void	create_pipe(t_pipex *pipex);
void	fork_process(t_pipex *pipex, char **av, char **envp);
void	child_process(t_pipex *pipex, char **av, char **envp);
void	parent_process(t_pipex *pipex, char **av, char **envp);
void	execute(char *cmd, t_pipex *pipex, char **envp);
char	**get_path(char **envp);
char	*search_correct_path(char *cmd, char **path);
void	free_array(char	**array);
void	free_and_exit(t_pipex *pipex, char **args, int code);

#endif
