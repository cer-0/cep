/* Diseñar una lista simple con los datos *
 * 1 No de partición
 * 2 Capacidad
 * 3 Localidad inicial
 * 4 Localidad final
 * 5 Estado
 * 6 Asignación
 * 7 Fragmentación interna */

#include <stdio.h>
#include <stdlib.h>

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
    int nuevo_elemento, r;
    do {
        if (Plista == NULL) {
            Plista = (nodo_lista *)malloc(sizeof(nodo_lista));

            printf("Ingresa el numero de particion: ");
            scanf("%d", &Plista->num_particion);

            printf("Ingresa la capacidad: ");
            scanf("%d", &Plista->capacidad);

            printf("Ingresa la localidad inicial: ");
            scanf("%d", &Plista->loc_inicial);

            printf("Ingresa la localidad final: ");
            scanf("%d", &Plista->loc_final);

            printf("Ingresa el estado: ");
            scanf("%d", &Plista->estado);

            printf("Ingresa la asignacion: ");
            scanf("%d", &Plista->asignacion);

            printf("Ingresa la fragmentacion interna: ");
            scanf("%d", &Plista->frag_interna);

            Plista->sig = NULL;
            Qlista = Plista;
        } else {
            Nuevolista = (nodo_lista *)malloc(sizeof(nodo_lista));

            printf("Ingresa el numero de particion: ");
            scanf("%d", &Nuevolista->num_particion);

            printf("Ingresa la capacidad: ");
            scanf("%d", &Nuevolista->capacidad);

            printf("Ingresa la localidad inicial: ");
            scanf("%d", &Nuevolista->loc_inicial);

            printf("Ingresa la localidad final: ");
            scanf("%d", &Nuevolista->loc_final);

            printf("Ingresa el estado: ");
            scanf("%d", &Nuevolista->estado);

            printf("Ingresa la asignacion: ");
            scanf("%d", &Nuevolista->asignacion);

            printf("Ingresa la fragmentacion interna: ");
            scanf("%d", &Nuevolista->frag_interna);

            Nuevolista->sig = NULL;

            Qlista->sig = Nuevolista;
            Qlista = Nuevolista;
        }
        printf("\nDesea ingresar otro elemento? (1 si, 0 no): ");
        scanf("%d", &r);
    } while (r == 1);
}

void ver_lista(void) {
    Aux = Plista;
    printf("\nNo particion\tCapacidad\tLoc inicial\tLoc final\tEstado\t\tAsignacion\tFrag interna");
    while (Aux != NULL) {
        printf("\n%d \t\t%d \t\t%d \t\t%d \t\t%d \t\t%d \t\t%d",
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
