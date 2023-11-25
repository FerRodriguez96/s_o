// librerias a incluir
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// libreria para manejar lectura de directorios
#include <dirent.h>
// libreria para obtener informacion de directorios
#include <sys/stat.h>
// libreria para tener constantes de limites de sistema
#include <linux/limits.h>

/*Escriba un programa que recibe un parámetro obligatorio y dos
parámetros opcionales. El parámetro obligatorio es una palabra y los opcionales son un
directorio y la letra “e”. Si se recibe el parámetro de directorio el proceso debe cambiar su
directorio de trabajo a dicho directorio y si no puede realizarse esto debe terminar. El
programa luego debe imprimir el directorio de trabajo actual y todos los ficheros o directorios
contenidos en el mismo (sin entrar en subdirectorios) que contengan la palabra pasada
como parámetro al programa. Aparte de lo indicado el programa debe imprimir la cantidad
de bytes ocupados por dichos ficheros o directorios agrupándolos en “Archivos Regulares”,
“Directorios” y “Otros Archivos” (no se preocupe si hay hard-links a un mismo archivo).
Si se especifica el tercer parámetro debe eliminar los archivos que no sean archivos
regulares o directorios que contengan la palabra pasada como parámetro al programa.
*/

void imprimir_contenido(char *ruta, char *palabra, int bandera_eliminacion)
{
    // declaracion de estructuras
    DIR *dirp;
    struct dirent *direntp;
    struct stat atributos;

    // declaracion de variables
    long long cant_reg = 0, cant_dir = 0, cant_otr = 0;

    // apertura de directorio
    dirp = opendir(".");

    // comprobacion de apertura correcta
    if (dirp == NULL)
    {
        perror("Error al abrir el directorio");
        exit(1);
    }

    // lectura de directorio
    while ((direntp = readdir(dirp)) != NULL)
    {
        // busqueda de la palabra dentro de los nombres del directorio
        if (strstr(direntp->d_name, palabra) != NULL)
        {
            printf("Contiene la palabra: %s\n", direntp->d_name);

            // obtencion de atributos de directorio
            if (stat(direntp->d_name, &atributos) == 0)
            {
                if (S_ISREG(atributos.st_mode) != 0)
                {
                    // suma de bytes de archivos regulares
                    cant_reg += atributos.st_size;
                }
                else if (S_ISDIR(atributos.st_mode) != 0)
                {
                    // suma de bytes de directorios
                    cant_dir += atributos.st_size;
                }
                else
                {
                    printf("%s es otro archivo\n", direntp->d_name);

                    // suma de bytes de otros archivos
                    cant_otr += atributos.st_size;

                    // eliminacion de otros archivos si se ingreso el parametro "e"
                    if (bandera_eliminacion == 1)
                    {
                        if (unlink(direntp->d_name) == -1)
                        {
                            perror("Error al eliminar el archivo");
                            exit(1);
                        }
                        else
                        {
                            printf("Se ha eliminado el archivo: %s\n", direntp->d_name);
                        }
                    }
                }
            }
        }
    }

    // impresion de valores de bytes
    printf("La cantidad de bytes que ocupan los archivos regulares es de %lld\n", cant_reg);
    printf("La cantidad de bytes que ocupan los directorios es de %lld\n", cant_dir);
    printf("La cantidad de bytes que ocupan otros archivos es de %lld\n", cant_otr);

    // cierre de directorio
    closedir(dirp);
}

int main(int argc, char *argv[])
{
    // comprobacion de numero de argumentos
    if (argc < 2 || argc > 4)
    {
        printf("Error en la cantidad de argumentos ingresados\n");
        exit(1);
    }

    // asigna la palabra al primer argumento
    char *palabra = argv[1];

    // declaracion de buffer
    char buf[PATH_MAX];

    // se obtiene el directorio actual
    if (getcwd(buf, PATH_MAX) == NULL)
    {
        perror("getcwd");
        exit(1);
    }
    else
    {
        printf("Directorio actual: %s\n", buf);
    }

    printf("Cambiando directorio...\n");

    if (argc >= 3)
    {
        // cambio de directorio
        if (chdir(argv[2]) == -1)
        {
            perror("chdir");
            exit(1);
        }

        printf("Nuevo directorio: %s\n", argv[2]);
    }
    /*
        En primer lugar, se verifica que se tienen 4 argumentos
        y en segundo, si el argumento 4 es igual a "e".
        Esta comparacion se logra mediante strcmp, que da
        "0" en caso de ser afirmativa la comparacion.

        En caso de que ambas condiciones se cumplan, la bandera
        de eliminar la palabra pasa de 0 a 1.
    */

    int bandera_eliminar = 0;

    if (argc == 4 && strcmp("e", argv[3]) == 0)
    {
        bandera_eliminar = 1;
    }

    // llamado de funcion
    imprimir_contenido(buf, palabra, bandera_eliminar);

    return 0;
}