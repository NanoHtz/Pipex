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

void	execute_command(char *cmd, char **envp);
void	parent_process(int fd[], char **envp, char **av);
void	child_process(int fd[], char **envp, char **av);
char	*is_executable(char *cmd_path, char **paths);
char	**get_paths(char **envp);
char	*find_command_path(char *cmd, char **envp);

#endif
