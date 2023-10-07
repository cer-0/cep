#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACIDAD_MEMORIA 2048 // en kilobytes
#define MARCO_PAGINA      32768 // en bytes
#define MARCOS_SO         3
#define LINEAS_CODIGO_PP  100 // por página
#define NUM_TAREAS        15

typedef struct tabla_mapa_memoria {
    int num_marco;
    int localidad_inicio;
    int estado;
    struct tabla_mapa_memoria *siguiente;
} TablaMapaMemoria;

typedef struct tabla_tareas {
    int num_tarea;
    int num_lineas_codigo;
    int localidad_pmt;
    struct tabla_tareas *siguiente;
} TablaTareasNodo;

typedef struct tabla_mapa_paginas {
    int num_pagina;
    int localidad_marco;
    struct tabla_mapa_paginas *siguiente;
} TablaMapaPaginas;

void tmm_lista_crear(void);
void tmm_lista_ver(void);
void tt_lista_crear(void);
void tt_lista_ver(void);
int  aleatorio_crear(int, int);
void paginacion_simple(void);
void obten_frag_interna(void);

TablaMapaMemoria *TMMCabeza, *TMMCola, *TMMNuevo, *TMMAux;
TablaTareasNodo  *TTCabeza, *TTCola, *TTNuevo, *TTAux;
TablaMapaPaginas *TMP[NUM_TAREAS], *TMPAux;

int num_marcos_mem  = (CAPACIDAD_MEMORIA * 1024) / MARCO_PAGINA;
int num_marcos_disp = ((CAPACIDAD_MEMORIA * 1024) / MARCO_PAGINA) - MARCOS_SO;

int main() {
    TMMCabeza = NULL, TMMCola = NULL;
    TTCabeza  = NULL, TTCola  = NULL;
    srand(time(NULL));
    tmm_lista_crear();
    tmm_lista_ver();
    tt_lista_crear();
    tt_lista_ver();
    paginacion_simple();
    tmm_lista_ver();
    return 0;
}

int aleatorio_crear(int min, int max) {
    /* Devuelve un número aleatorio entre 'min' y 'max' */
    return ((rand() % (max - min)) + min);
}

void tmm_lista_crear(void) {
    /* Conversión de KiloBytes a Bytes */
    /* Creación de marcos para el SO */
    for(int i = 0; i < MARCOS_SO; i++) {
        if(TMMCabeza == NULL) {
            TMMCabeza = (TablaMapaMemoria *)malloc(sizeof(TablaMapaMemoria));
            TMMCabeza->num_marco        = i;
            TMMCabeza->localidad_inicio = i * MARCO_PAGINA;
            TMMCabeza->estado           = 1;
            TMMCabeza->siguiente        = NULL;
            TMMCola = TMMCabeza;
        } else {
            TMMNuevo = (TablaMapaMemoria *)malloc(sizeof(TablaMapaMemoria));
            TMMNuevo->num_marco        = i;
            TMMNuevo->localidad_inicio = i * MARCO_PAGINA;
            TMMNuevo->estado           = 1;
            TMMCola->siguiente         = TMMNuevo;
            TMMNuevo->siguiente        = NULL;
            TMMCola = TMMNuevo;
        }
    }
    /* Creación de marcos de página restantes */
    for(int i = MARCOS_SO; i < num_marcos_mem; i++) {
        TMMNuevo = (TablaMapaMemoria *)malloc(sizeof(TablaMapaMemoria));
        TMMNuevo->num_marco        = i;
        TMMNuevo->localidad_inicio = i * MARCO_PAGINA;
        TMMNuevo->estado           = 0;
        TMMCola->siguiente         = TMMNuevo;
        TMMNuevo->siguiente = NULL;
        TMMCola = TMMNuevo;
    }
}

void tmm_lista_ver(void) {
    TMMAux = TMMCabeza;
    printf("+----------+------------+--------+\n");
    printf("| No marco | Loc inicio | Estado |\n");
    printf("+----------+------------+--------+\n");
    while (TMMAux != NULL) {
        printf("| %-8d | %-10d | %-6d |\n",
                TMMAux->num_marco,
                TMMAux->localidad_inicio,
                TMMAux->estado);
        TMMAux = TMMAux->siguiente;
    }
    printf("+----------+------------+--------+\n\n");
}

void tt_lista_crear(void) {
    for(int i = 0; i < NUM_TAREAS; i++) {
        if(TTCabeza == NULL) {
            TTCabeza = (TablaTareasNodo *)malloc(sizeof(TablaTareasNodo));
            TTCabeza->num_tarea         = i + 1; // Evitamos que haya tarea 0
            TTCabeza->num_lineas_codigo = aleatorio_crear(500, 1000);
            TTCabeza->localidad_pmt     = -1; // No asignamos dirección
            TTCabeza->siguiente = NULL;
            TTCola = TTCabeza;
        } else {
            TTNuevo = (TablaTareasNodo *)malloc(sizeof(TablaTareasNodo));
            TTNuevo->num_tarea         = i + 1;
            TTNuevo->num_lineas_codigo = aleatorio_crear(99, 520);
            TTNuevo->localidad_pmt     = -1;
            TTNuevo->siguiente         = NULL;
            TTCola->siguiente = TTNuevo;
            TTCola = TTNuevo;
        }
    }
}

void tt_lista_ver(void) {
    TTAux = TTCabeza;
    printf("+----------+------------+---------+\n");
    printf("| No tarea | Lineas cod | Loc PMT |\n");
    printf("+----------+------------+---------+\n");
    while (TTAux != NULL) {
        printf("| %-8d | %-10d | %-7d |\n",
                TTAux->num_tarea,
                TTAux->num_lineas_codigo,
                TTAux->localidad_pmt);
        TTAux = TTAux->siguiente;
    }
    printf("+----------+------------+---------+\n\n");
}

void paginacion_simple(void) {
    /* Iteramos las tareas para asignar marcos en la tabla de mapa de memoria */
    TTAux = TTCabeza;
    for(int i = 0; i < NUM_TAREAS; i++) {
        TMMAux = TMMCabeza;
        int lin_codigo_tarea = TTAux->num_lineas_codigo;
        for(int j = 0; j < num_marcos_mem; j++) {
            /* Checar qué pasa cuando esto el numero de lineas de código 0 */
            if(lin_codigo_tarea > 0 && lin_codigo_tarea < (num_marcos_disp * LINEAS_CODIGO_PP)) {
                if(TMMAux->estado == 0) {
                    printf("Asignando J%d en marco %d\n", TTAux->num_tarea, TMMAux->num_marco);
                    lin_codigo_tarea -= 100;
                    TMMAux->estado = 1;
                }
            }
        }
        TMMAux = TMMAux->siguiente;
    }
    TTAux = TTAux->siguiente;
}

/* void obten_frag_interna(void) { */
/* } */
