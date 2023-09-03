#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define tam_arr 20

int main() {
    int  longitud,
         estado = 0,
         posicion = 0;
    char entrada[tam_arr];

    printf("Ingresa cadena: ");
    fgets(entrada, tam_arr, stdin);
    printf("Ingresaste: %s\n", entrada);

    longitud = strlen(entrada);

    while(posicion < longitud - 1) {
        switch(estado) {
            case 0:
                if(isalpha(entrada[posicion]))
                    estado = 1;
                else
                    estado = 2;
                break;
            case 1:
                if(isalnum(entrada[posicion]))
                    estado = 1;
                else
                    estado = 2;
                break;
            case 2:
                break;
        }
        posicion++;
    }

    if(estado == 1)
        printf("Nombre de variable válido\n");
    else
        printf("Nombre de variable no válido\n");

    return 0;
}
