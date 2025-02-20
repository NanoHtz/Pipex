/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_value_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:31:08 by fgalvez-          #+#    #+#             */
/*   Updated: 2024/12/08 13:31:08 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	ft_min_error(const char *str)
{
	write(1, "\033[31m", 5);
	ft_strendl(str);
	write(1, "\033[0m", 4);
	return (INT_MIN);
}

int	ft_max_error(const char *str)
{
	write(1, "\033[31m", 5);
	ft_strendl(str);
	write(1, "\033[0m", 4);
	return (INT_MAX);
}
