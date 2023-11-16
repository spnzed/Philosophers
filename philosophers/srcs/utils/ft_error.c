/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:47:33 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/16 18:59:27 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error(char *str)
{
	printf ("%s%s%s\n", RED, str, RESET);
	exit(EXIT_FAILURE);
}


/*

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

void cleanupAndExit(int exitCode) {
    // Realiza aquí todas las operaciones de limpieza necesarias, como liberar memoria dinámica.

    // Imprime un mensaje de salida (puedes personalizarlo según tus necesidades)
    printf("%s%s%s\n", RED, "Saliendo del programa...", RESET);

    // Liberar la memoria dinámica, cerrar archivos, etc.

    // Finalmente, salir del programa con el código de salida proporcionado.
    // En lugar de exit, podrías regresar a la función que llamó a la tuya.
    // O, si estás en la función principal, podrías usar un bucle para salir
    // de manera controlada.
    exit(exitCode);
}

int main() {
    // Algo de código...

    // Llamada a la función de salida personalizada
    cleanupAndExit(EXIT_FAILURE);

    // El código aquí no se ejecutará después de llamar a cleanupAndExit.
    // Puedes devolver un valor si es necesario, pero en este ejemplo, no es alcanzable.
    return 0;
}

*/