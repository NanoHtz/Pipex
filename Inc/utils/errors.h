/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:15:22 by fgalvez-          #+#    #+#             */
/*   Updated: 2024/12/05 14:58:44 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ARGS_ERROR "There must be 4 arguments"
# define OPEN_ERROR_OUTFILE "Error opening outfile"
# define OPEN_ERROR_INFILE "Error opening infile"
# define PIPE_ERROR "Error making pipe"
# define FORK_ERROR "Error making fork"
# define EXECVE_ERROR "Error making execve"
# define COMMAND_NOT_FOUND "Command not found"
# define MEMORY_ERROR "Error making memory"
# define MALLOC_ERROR "Error making malloc"
# define COMMAND_ERROR "Error: Command not found"
# define INT_MIN -2147483648
# define INT_MAX 2147483647

# include <unistd.h>
# include <stdlib.h>

//Basic
void	ft_strendl(const char *str);
//Errors
int		ft_error(const char *str);
void	ft_void_error(const char *str);
int		*ft_ptr_error(const char *str);
int		ft_max_error(const char *str);
int		ft_min_error(const char *str);
//Warnings
void	ft_warning(const char *str);
//Sucess
void	ft_success(const char *str);

#endif
