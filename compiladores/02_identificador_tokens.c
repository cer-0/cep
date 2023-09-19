#include <stdio.h>
#include <string.h>
#include <ctype.h>

void token_identifica(char * cadena);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Uso: identificador_tokes cadena\n");
        return 1;
    }
    token_identifica(argv[1]);
    return 0;
}

void token_identifica(char * cadena)
{
    int  longitud,
         estado = 0,
         posicion = 0;

    longitud = strlen(cadena);

    while(posicion < longitud)
    {
        switch(estado)
        {
            case -1:
                break;
            case 0:
                if(isdigit(cadena[posicion]))
                    estado = 2;
                else if(cadena[posicion] == '+' || cadena[posicion] == '-')
                    estado = 1;
                else if(isalpha(cadena[posicion]))
                    estado = 7;
                else if(cadena[posicion] == '<' || cadena[posicion] == '>')
                    estado = 8;
                else if(cadena[posicion] == '=')
                    estado = 10;
                else if(cadena[posicion] == '!')
                    estado = 12;
                else if(cadena[posicion] == '/' || cadena[posicion] == '*')
                    estado = 13;
                else if(cadena[posicion] == '&' || cadena[posicion] == '|')
                    estado = 14;
                else
                    estado = -1;
                break;
            case 1:
                if(isdigit(cadena[posicion]))
                    estado = 2;
                else
                    estado = -1;
                break;
            case 2:
                if(isdigit(cadena[posicion]))
                    estado = 2;
                else if(cadena[posicion] == '.')
                    estado = 3;
                else
                    estado = -1;
                break;
            case 3:
                if(isdigit(cadena[posicion]))
                    estado = 4;
                else
                    estado = -1;
                break;
            case 4:
                if(isdigit(cadena[posicion])) // coloqué estado en lugar de posicion
                    estado = 4;
                else if(cadena[posicion] == 'e' || cadena[posicion] == 'E')
                    estado = 5;
                else
                    estado = -1;
                break;
            case 5:
                if(cadena[posicion] == '+' || cadena[posicion] == '-')
                    estado = 6;
                else
                    estado = -1;
                break;
            case 6:
                if(isdigit(cadena[posicion]))
                    estado = 6;
                else
                    estado = -1;
                break;
            case 7:
                if(isalnum(cadena[posicion]))
                    estado = 7;
                else
                    estado = -1;
                break;
            case 8:
                if(cadena[posicion] == '=')
                    estado = 9;
                else
                    estado = -1;
                break;
            case 10:
                if(cadena[posicion] == '=')
                    estado = 11;
                else
                    estado = -1;
                break;
            case 12:
                if(cadena[posicion] == '=')
                    estado = 11;
                else
                    estado = -1;
                break;
            case 14:
                if(cadena[posicion] == '&' || cadena[posicion] == '|')
                    estado = 15;
                else
                    estado = -1;
                break;
        }
        posicion++;
    }
    switch(estado)
    {
        case 2:
            printf("Se identificó un número entero\n");
            break;
        case 4:
            printf("Se identificó un número decimal\n");
            break;
        case 6:
            printf("Se identificó un número exponencial\n");
            break;
        case 7:
            printf("Se identificó un nombre de variable\n");
            break;
        case 8:
        case 9:
        case 11:
            printf("Se identificó un operador relacional\n");
            break;
        case 1:
        case 13:
            printf("Se identificó un operador aritmético\n");
            break;
        case 12:
        case 15:
            printf("Se identificó un operador lógico\n");
            break;
        default:
            printf("Token desconocido\n");
            break;
    }
}

