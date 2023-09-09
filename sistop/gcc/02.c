#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define mem_so  20
#define mem_max 80

typedef struct nodo_lista {
    int num_particion;
    int capacidad;
    int loc_inicial;
    int loc_final;
    int estado;
    int asignacion;
    int frag_interna;
    struct nodo_lista *sig;
} nodo_lista;

void crear_lista(void);
void ver_lista(void);

nodo_lista *Plista, *Qlista, *Nuevolista, *Aux;

int main() {
    Plista = NULL;
    Qlista = NULL;
    crear_lista();
    ver_lista();
    return 0;
}

void crear_lista(void) {
    int r;
    do {
        if (Plista == NULL) {
            Plista = (nodo_lista *)malloc(sizeof(nodo_lista));

            Plista->num_particion = 0;
            Plista->capacidad     = mem_so;
            Plista->loc_inicial   = 0;
            Plista->loc_final     = mem_so - 1;
            Plista->estado        = 0;
            Plista->asignacion    = 0;
            Plista->frag_interna  = 0;

            Plista->sig = NULL;
            Qlista = Plista;
        } else {
            if(r == 1) {
                printf("\nCapacidad del bloque?: ");
                scanf("%d", &r);

                if(r < (mem_max - Qlista->loc_final)){
                    Nuevolista = (nodo_lista *)malloc(sizeof(nodo_lista));

                    Nuevolista->num_particion = Qlista->num_particion + 1;
                    Nuevolista->capacidad     = r;
                    Nuevolista->loc_inicial   = Qlista->loc_final + 1;
                    Nuevolista->loc_final     = (Nuevolista->loc_inicial 
                            + Nuevolista->capacidad) - 1;
                    Nuevolista->estado        = 1;
                    Nuevolista->asignacion    = 0;
                    Nuevolista->frag_interna  = 0;

                    Nuevolista->sig = NULL;

                    Qlista->sig = Nuevolista;
                    Qlista = Nuevolista;
                } else {
                    printf("\nExcediste el tamaño de bloque, disponible: %d",
                            (mem_max - Qlista->loc_final - 1));
                }
            }
        }
        printf("\nAgregar otro bloque? (1 si, 0 no): ");
        scanf("%d", &r);
    } while (r == 1);

    if((mem_max - 1) - Qlista->loc_final > 0) {
        Nuevolista = (nodo_lista *)malloc(sizeof(nodo_lista));

        Nuevolista->num_particion = Qlista->num_particion + 1;
        Nuevolista->capacidad     = (mem_max - Qlista->loc_final - 1);
        Nuevolista->loc_inicial   = Qlista->loc_final + 1;
        Nuevolista->loc_final     = (Nuevolista->loc_inicial 
                + Nuevolista->capacidad) - 1;
        Nuevolista->estado        = 1;
        Nuevolista->asignacion    = 0;
        Nuevolista->frag_interna  = 0;

        Nuevolista->sig = NULL;

        Qlista->sig = Nuevolista;
        Qlista = Nuevolista;
    }
}

void ver_lista(void) {
    Aux = Plista;
    printf("\nNo particion\tCapacidad\tLoc inicial\tLoc final\tEstado\t\tAsignacion\tFrag interna");
    while (Aux != NULL) {
        printf("\nP%d \t\t%dk \t\t%dk \t\t%dk \t\t%d \t\t%d \t\t%d",
                Aux->num_particion,
                Aux->capacidad,
                Aux->loc_inicial,
                Aux->loc_final,
                Aux->estado,
                Aux->asignacion,
                Aux->frag_interna);
        Aux = Aux->sig;
    }
    printf("\n");
}
