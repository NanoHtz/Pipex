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
	write(2, "\033[31m", 5);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	write(2, "\033[0m", 4);
	exit(1);
}

int	ft_error_command(const char *str)
{
	write(2, "\033[31m", 5);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	write(2, "\033[0m", 4);
	exit(127);
}
