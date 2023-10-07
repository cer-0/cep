#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define mem_so     20
#define mem_max    80
#define num_tareas 10

typedef struct tabla_memoria_nodo
{
    int num_particion;
    int capacidad;
    int loc_inicial;
    int loc_final;
    int estado;
    int asignacion;
    int frag_interna;
    struct tabla_memoria_nodo *sig;
} tabla_memoria_nodo;

typedef struct tabla_trabajos_nodo
{
    int num_tarea;
    int tamano;
    struct tabla_trabajos_nodo *sig;
} tabla_trabajos_nodo;

void tabla_memoria_crear(void);
void tabla_trabajos_crear(void);
void tabla_memoria_ver(void);
void tabla_trabajos_ver(void);

tabla_memoria_nodo   *tabla_memoria_pinicio, *tabla_memoria_pultimo, *tabla_memoria_preciente, *tabla_memoria_paux;
tabla_trabajos_nodo  *tabla_trabajos_pinicio, *tabla_trabajos_pultimo, *tabla_trabajos_preciente, *tabla_trabajos_paux;
int contador_particiones = 0;

int main()
{
    tabla_memoria_pinicio  = NULL;
    tabla_memoria_pultimo  = NULL;
    tabla_trabajos_pinicio = NULL;
    tabla_trabajos_pultimo = NULL;

    tabla_trabajos_crear();
    tabla_trabajos_ver();
    tabla_memoria_crear();
    tabla_memoria_ver();

    return 0;
}

void tabla_memoria_crear(void)
{
    int r;
    if(tabla_memoria_pinicio == NULL)
    {
        tabla_memoria_pinicio = (tabla_memoria_nodo *)malloc(sizeof(tabla_memoria_nodo));

        tabla_memoria_pinicio->num_particion = 0;
        tabla_memoria_pinicio->capacidad     = mem_so;
        tabla_memoria_pinicio->loc_inicial   = 0;
        tabla_memoria_pinicio->loc_final     = mem_so - 1;
        tabla_memoria_pinicio->estado        = 0;
        tabla_memoria_pinicio->asignacion    = 0;
        tabla_memoria_pinicio->frag_interna  = 0;

        tabla_memoria_pinicio->sig = NULL;
        tabla_memoria_pultimo = tabla_memoria_pinicio;
        contador_particiones++;
    }
    tabla_trabajos_paux = tabla_trabajos_pinicio;
    while(tabla_trabajos_paux != NULL)
    {
        if(tabla_trabajos_paux->tamano < (mem_max - tabla_memoria_pultimo->loc_final))
        {
            tabla_memoria_preciente = (tabla_memoria_nodo *)malloc(sizeof(tabla_memoria_nodo));

            tabla_memoria_preciente->num_particion = tabla_memoria_pultimo->num_particion + 1;
            tabla_memoria_preciente->capacidad     = tabla_trabajos_paux->tamano;
            tabla_memoria_preciente->loc_inicial   = tabla_memoria_pultimo->loc_final + 1;
            tabla_memoria_preciente->loc_final     = (tabla_memoria_preciente->loc_inicial + tabla_memoria_preciente->capacidad) - 1;
            tabla_memoria_preciente->estado        = 0;
            tabla_memoria_preciente->asignacion    = tabla_trabajos_paux->num_tarea;
            tabla_memoria_preciente->frag_interna  = 0;
            tabla_memoria_preciente->sig           = NULL;

            tabla_memoria_pultimo->sig             = tabla_memoria_preciente;
            tabla_memoria_pultimo                  = tabla_memoria_preciente;
            contador_particiones++;
        }
        tabla_trabajos_paux = tabla_trabajos_paux->sig;
    }


    if((mem_max - 1) - tabla_memoria_pultimo->loc_final > 0)
    {
        tabla_memoria_preciente = (tabla_memoria_nodo *)malloc(sizeof(tabla_memoria_nodo));

        tabla_memoria_preciente->num_particion = tabla_memoria_pultimo->num_particion + 1;
        tabla_memoria_preciente->capacidad     = (mem_max - tabla_memoria_pultimo->loc_final - 1);
        tabla_memoria_preciente->loc_inicial   = tabla_memoria_pultimo->loc_final + 1;
        tabla_memoria_preciente->loc_final     = (tabla_memoria_preciente->loc_inicial + tabla_memoria_preciente->capacidad) - 1;
        tabla_memoria_preciente->estado        = 1;
        tabla_memoria_preciente->asignacion    = -1;
        tabla_memoria_preciente->frag_interna  = (mem_max - 1) - tabla_memoria_pultimo->loc_final;

        tabla_memoria_preciente->sig = NULL;

        tabla_memoria_pultimo->sig = tabla_memoria_preciente;
        tabla_memoria_pultimo = tabla_memoria_preciente;
        contador_particiones++;
    }
}

void tabla_trabajos_crear(void)
{
    srand(time(NULL));
    tabla_trabajos_pinicio = (tabla_trabajos_nodo *)malloc(sizeof(tabla_trabajos_nodo));

    tabla_trabajos_pinicio->num_tarea = 1;
    tabla_trabajos_pinicio->tamano    = (rand() % 40) + 5;
    tabla_trabajos_pinicio->sig       = NULL;

    tabla_trabajos_pultimo = tabla_trabajos_pinicio;

    for(int i = 1; i < num_tareas; i++)
    {
        tabla_trabajos_preciente =(tabla_trabajos_nodo *)malloc(sizeof(tabla_trabajos_nodo));

        tabla_trabajos_preciente->num_tarea = i + 1;
        tabla_trabajos_preciente->tamano    = (rand() % 40) + 5;
        tabla_trabajos_preciente->sig       = NULL;

        tabla_trabajos_pultimo->sig = tabla_trabajos_preciente;
        tabla_trabajos_pultimo = tabla_trabajos_preciente;
    }
}

void tabla_memoria_ver(void)
{
    tabla_memoria_paux = tabla_memoria_pinicio;
    printf("\nNo particion\tCapacidad\tLoc inicial\tLoc final\tEstado\t\tAsignacion\tFrag interna");
    while (tabla_memoria_paux != NULL)
    {
        printf("\nP%d \t\t%dk \t\t%dk \t\t%dk \t\t%d \t\tJ%d \t\t%d",
                tabla_memoria_paux->num_particion,
                tabla_memoria_paux->capacidad,
                tabla_memoria_paux->loc_inicial,
                tabla_memoria_paux->loc_final,
                tabla_memoria_paux->estado,
                tabla_memoria_paux->asignacion,
                tabla_memoria_paux->frag_interna);
        tabla_memoria_paux = tabla_memoria_paux->sig;
    }
    printf("\n");
}

void tabla_trabajos_ver(void)
{
    tabla_trabajos_paux = tabla_trabajos_pinicio;

    printf("\nNo tarea\tTamaño");
    while(tabla_trabajos_paux != NULL)
    {
        printf("\nJ%d\t\t%dk", tabla_trabajos_paux->num_tarea, tabla_trabajos_paux->tamano);
        tabla_trabajos_paux = tabla_trabajos_paux->sig;
    }
    printf("\n");
}
