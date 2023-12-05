#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Limpiar el entorno
    clearenv();

    // Verificar si se proporcionan argumentos de línea de comandos para definir variables de entorno
    if (argc > 1) {
        // Navegar a través de los argumentos y agregar las definiciones de entorno
        for (int i = 1; i < argc; i++) {
            char *env_definition = argv[i];
            if (putenv(env_definition) != 0) {
                perror("Error al definir una variable de entorno");
                exit(1);
            }
        }
    }

    // Imprimir la lista de entorno actualizada
    char **env = __environ;
    printf("Entorno actualizado:\n");
    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}