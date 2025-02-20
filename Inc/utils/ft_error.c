/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:16:53 by fgalvez-          #+#    #+#             */
/*   Updated: 2024/12/05 13:54:38 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	ft_error(const char *str)
{
	write(1, "\033[31m", 5);
	ft_strendl(str);
	write(1, "\033[0m", 4);
	return (-1);
}

int	*ft_ptr_error(const char *str)
{
	write(1, "\033[31m", 5);
	ft_strendl(str);
	write(1, "\033[0m", 4);
	return (NULL);
}

void	ft_void_error(const char *str)
{
	write(1, "\033[31m", 5);
	ft_strendl(str);
	write(1, "\033[0m", 4);
}
