#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tabla_simbolos_nodo {
    char* lexema;
    char* token;
    struct tabla_simbolos_nodo *siguiente;
} TablaSimbolosNodo;

int  token_identifica_palabra_reservada(char * cadena);
void token_identifica(char * cadena);
void token_agrega_a_tabla_de_simbolos(char * lexema, char * token);
void muestra_tabla_de_simbolos(void);

TablaSimbolosNodo *ts_cabeza, *ts_cola, *ts_nuevo, *ts_aux;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Uso: %s archivo\n", argv[0]);
        exit(1);
    }
    char * entrada;
    long archivo_longitud;
    FILE *archivo_ptr = fopen(argv[1], "r");
    if(archivo_ptr == NULL) {
        printf("Archivo inválido\n");
        exit(1);
    }

    fseek(archivo_ptr, 0, SEEK_END);
    archivo_longitud = ftell(archivo_ptr);
    fseek(archivo_ptr, 0, SEEK_SET);
    entrada = malloc(archivo_longitud);
    if(entrada == NULL) {
        printf("Error asignando memoria\n");
        exit(1);
    }
    fread(entrada, 1, archivo_longitud, archivo_ptr);
    fclose(archivo_ptr);

    int num_saltos_lin = 0;
    for(int i = 0; i < archivo_longitud; i++) {
        if(entrada[i] == '\n')
            num_saltos_lin++;
    }

    for(int i = 0; i< num_saltos_lin; i++)
        entrada[strcspn(entrada, "\n")] = ' ';

    ts_cabeza = NULL, ts_cola = NULL;
    for(char *p = strtok(entrada, " "); p != NULL; p = strtok(NULL, " "))
        token_identifica(p);

    muestra_tabla_de_simbolos();
    return 0;
}

void token_identifica(char *cadena) {
    int  longitud,
         estado = 0,
         posicion = 0;

    longitud = strlen(cadena);

    while(posicion < longitud) {
        switch(estado) {
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
                if(isdigit(cadena[posicion]))
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
    char* lexema;
    char* token;
    switch(estado) {
        case -1:
            token_agrega_a_tabla_de_simbolos(cadena, "desconocido");
            break;
        case 2:
            token_agrega_a_tabla_de_simbolos(cadena, "entero");
            break;
        case 4:
            token_agrega_a_tabla_de_simbolos(cadena, "decimal");
            break;
        case 6:
            token_agrega_a_tabla_de_simbolos(cadena, "exponencial");
            break;
        case 7:
            if(token_identifica_palabra_reservada(cadena) == 1)
                token_agrega_a_tabla_de_simbolos(cadena, "palabra reservada");
            else
                token_agrega_a_tabla_de_simbolos(cadena, "nombre de variable");
            break;
        case 8:
        case 9:
        case 11:
            token_agrega_a_tabla_de_simbolos(cadena, "operador relacional");
            break;
        case 1:
        case 13:
            token_agrega_a_tabla_de_simbolos(cadena, "operador aritmetico");
            break;
        case 12:
        case 15:
            token_agrega_a_tabla_de_simbolos(cadena, "operador logico");
            break;
        default:
            token_agrega_a_tabla_de_simbolos(cadena, "desconocido");
            break;
    }
}

int token_identifica_palabra_reservada(char *cadena) {
    if(strcmp(cadena, "if") == 0)
        return 1;
    else if(strcmp(cadena, "else") == 0)
        return 1;
    else if(strcmp(cadena, "while") == 0)
        return 1;
    else if(strcmp(cadena, "do") == 0)
        return 1;
    else if(strcmp(cadena, "for") == 0)
        return 1;
    else if(strcmp(cadena, "printf") == 0)
        return 1;
}

void token_agrega_a_tabla_de_simbolos(char * lexema, char * token) {
    if(ts_cabeza == NULL) {
        ts_cabeza = (TablaSimbolosNodo *)malloc(sizeof(TablaSimbolosNodo));
        ts_cabeza->lexema = lexema;
        ts_cabeza->token  = token;
        ts_cabeza->siguiente = NULL;
        ts_cola = ts_cabeza;
    } else {
        ts_nuevo = (TablaSimbolosNodo *)malloc(sizeof(TablaSimbolosNodo));
        ts_nuevo->lexema = lexema;
        ts_nuevo->token  = token;
        ts_nuevo->siguiente = NULL;
        ts_cola->siguiente = ts_nuevo;
        ts_cola = ts_nuevo;
    }
}

void muestra_tabla_de_simbolos(void) {
    ts_aux = ts_cabeza;
    printf("+----------------------+----------------------+\n");
    printf("|              Tabla de Símbolos              |\n");
    printf("+----------------------+----------------------+\n");
    printf("| %-20s | %-20s |\n", "lexema", "token");
    printf("+----------------------+----------------------+\n");
    while(ts_aux != NULL) {
        printf("| %-20s | %-20s |\n", ts_aux->lexema, ts_aux->token);
        ts_aux = ts_aux->siguiente;
    }
    printf("+----------------------+----------------------+\n");
}
