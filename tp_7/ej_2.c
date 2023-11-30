#include <stdio.h>
#include <stdlib.h>

/*
    Utilizando la función calloc(), escriba un programa que asigne espacio para un arreglo de
    valores enteros. y permita cargar el arreglo. Una vez cargado el arreglo debe imprimir los
    valores cargados anteriormente.
*/

int main(int argc, char* argv[]){

    // comprobacion de argumento
    if (argc < 0){
        printf("No se han ingresado suficientes argumentos\n");
        exit(1);
    }
    
    // declaracion de variable tamaño
    int tamano;

    // Se le solicita al usuario el tamaño del arreglo
    printf("Ingrese la cantidad de numeros que quiere guardar en el arreglo\n");
    scanf("%d", &tamano);

    // Se asigna al arreglo el tamaño ingresado
    int *arreglo = calloc(tamano, sizeof(int));

    //comprobacion de asignacion de memoria correcta
    if (arreglo == NULL){
        perror("Asignacion de memoria fallida\n");
        exit(1);
    }
    else{
        printf("Asignacion de memoria exitosa\n");

        // carga del arreglo
        printf("Ingrese %d numeros nuevos al arreglo:\n", tamano);
            for(int i = 0; i < tamano; i++){
                scanf("%d", &arreglo[i]);
            }

        // se imprime el arreglo con los nuevos valores
        for(int i= 0; i < tamano; i++){
                printf("El arreglo en la posicion %d contiene: %d \n",i , arreglo[i]);
            }

        free(arreglo);
    }

    return 0;
}