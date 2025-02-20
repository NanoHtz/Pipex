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

/*
*** Debemos replicar el funcionamiento de los pipex en UNIX
*** El programa funcionara asi: ./pipex archivo1 comando1 comando2 archivo2
*** Replicando el comportamiento de:
*** < archivo1 comando1 | comando2 > archivo2
*** Ejemplo, esto: ./pipex infile "ls -l" "wc -l" outfile
*** debe replicar el comportamiento de esto: < infile ls -l | wc -l > outfile
*** Se permite usar: open, close, read, write, malloc, free, perror, strerror
*** access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
*** ft_printf y similares.
*** Debe entregarse con un makefile con las reglas: NAME, all, clean, fclean, re.
*** Debe cumplir la norma y no tener fugas de memoria.
*** El bonus deble poder manejar mas de dos comandos
*** ./pipex archivo1 comando1 comando2 comando3 ... comandon archivo2
*** Implementar here_doc
*** PASOS:
*** pipe() y fork() son las bases del proyecto, entiendelas bien.
*** Implementa un simple pipeline (cmd1 | cmd2) con dup2() y execve().
*** Gestiona errores correctamente (archivos, comandos, argumentos incorrectos).
*** Añade el manejo de argv para ejecutar los comandos correctamente.
*** Optimiza la gestión de memoria para evitar leaks.
*** Prueba con diferentes casos de uso y usa valgrind para verificar memoria.
*/

#include "../Inc/pipex.h"
<<<<<<< HEAD

int	main(int ac, char **av)
{
	int	fd;
	int	fd2;

	(void)av;
	if (ac == 5)
	{
		fd = open(av[1], O_RDONLY);
		fd2 = open(av[5], O_WRONLY );
		if ((fd == -1) || (fd2 == - 1))
			ft_error(OPEN_ERROR);

		printf("Hola caracola\n");
	}
	else
		ft_error(ARGS_ERROR);
}
=======
>>>>>>> 791456deaa6bff4ce01e5341b180b2c0b1c018e6
