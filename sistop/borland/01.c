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
#include <conio.h>

void crear_lista(void);
void ver_lista(void);

struct nodo_lista
{
    int num_particion;
    int capacidad;
    int loc_inicial;
    int loc_final;
    int estado;
    int asignacion;
    int frag_interna;
    nodo_lista *sig;
};

nodo_lista *Plista, *Qlista, *Nuevolista, *Aux;

int main()
{
    Plista = NULL;
    Qlista = NULL;
    crear_lista();
    ver_lista();
    return 0;
}

void crear_lista(void)
{
    int nuevo_elemento, r;
    do
    {
        if (Plista == NULL)
        {
            Plista = (nodo_lista *)malloc(sizeof(nodo_lista));

            printf("Ingresa el numero de particion: ");
            scanf("%d", &nuevo_elemento);
            Plista->num_particion = nuevo_elemento;

            printf("Ingresa la capacidad: ");
            scanf("%d", &nuevo_elemento);
            Plista->capacidad = nuevo_elemento;

            printf("Ingresa la localidad inicial: ");
            scanf("%d", &nuevo_elemento);
            Plista->loc_inicial = nuevo_elemento;

            printf("Ingresa la localidad final: ");
            scanf("%d", &nuevo_elemento);
            Plista->loc_final = nuevo_elemento;

            printf("Ingresa el estado: ");
            scanf("%d", &nuevo_elemento);
            Plista->estado = nuevo_elemento;

            printf("Ingresa la asignacion: ");
            scanf("%d", &nuevo_elemento);
            Plista->asignacion = nuevo_elemento;

            printf("Ingresa la fragmentacion interna: ");
            scanf("%d", &nuevo_elemento);
            Plista->frag_interna = nuevo_elemento;

            Plista->sig = NULL;
            Qlista = Plista;
        }
        else
        {
            Nuevolista = (nodo_lista *)malloc(sizeof(nodo_lista));

            printf("Ingresa el numero de particion: ");
            scanf("%d", &nuevo_elemento);
            Nuevolista->num_particion = nuevo_elemento;

            printf("Ingresa la capacidad: ");
            scanf("%d", &nuevo_elemento);
            Nuevolista->capacidad = nuevo_elemento;

            printf("Ingresa la localidad inicial: ");
            scanf("%d", &nuevo_elemento);
            Nuevolista->loc_inicial = nuevo_elemento;

            printf("Ingresa la localidad final: ");
            scanf("%d", &nuevo_elemento);
            Nuevolista->loc_final = nuevo_elemento;

            printf("Ingresa el estado: ");
            scanf("%d", &nuevo_elemento);
            Nuevolista->estado = nuevo_elemento;

            printf("Ingresa la asignacion: ");
            scanf("%d", &nuevo_elemento);
            Nuevolista->asignacion = nuevo_elemento;

            printf("Ingresa la fragmentacion interna: ");
            scanf("%d", &nuevo_elemento);
            Nuevolista->frag_interna = nuevo_elemento;

            Nuevolista->sig = NULL;

            Qlista->sig = Nuevolista;
            Qlista = Nuevolista;
        }
        printf("\nDesea ingresar otro elemento? (1 si, 0 no): ");
        scanf("%d", &r);
    } while (r == 1);
    getch();
}

void ver_lista(void)
{
    Aux = Plista;
    printf("\nNo particion\tCapacidad\tLoc inicial\tLoc final\tEstado\t\tAsignacion\tFrag interna");
    while (Aux != NULL)
    {
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
}
