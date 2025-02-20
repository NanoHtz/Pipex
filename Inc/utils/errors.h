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
# define OPEN_ERROR "Error opening file"
# define INT_MIN -2147483648
# define INT_MAX 2147483647

# include <unistd.h>

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
