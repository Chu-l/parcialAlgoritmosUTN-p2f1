/*
Algoritmos y Estructura de Datos – 2025 – SEGUNDO PARCIAL – S 14 – 10-11-2025 – TEMA 1

Proponer una estrategia de abordaje a la resolución del problema planteado – OBLIGATORIO
Con los conocimientos que dispone actualmente diseñar una solución y desarrollar un programa en C.
Se deberá declarar todas las estructuras utilizadas en la solución.

Enunciado:

En un evento al aire libre, el personal de seguridad lleva el control e ingreso de los espectadores, los cuales tienen tipos de ubicaciones: A, B y C, de la siguiente forma:

Se escanea el QR donde figura el número de ticket y ubicación. Esta información está en una lista previamente cargada de la venta de los tickets.
Los espectadores que acceden al evento son cargados en una cola de espera.
En el segundo control se habilitan las ubicaciones y la cola de espera, cada espectador se carga en una lista ordenada por ubicación.
Al iniciar el evento no ingresan más espectadores.

Actividades

Desarrollar toda la operatoria del personal de seguridad.
Al iniciar el evento se quiere obtener la siguiente información de control:

a. Qué porcentaje de espectadores asistieron sobre la venta de los tickets.
b. Qué cantidad de espectadores asistieron a cada ubicación.

* El punto 2) debe ser recursivo.
*/
/*
ESTRATEGIA
1- GENERAR LA LISTA DE ENTRADAS VENDIDAS
2- SE CREA UNA COLA DE ESPERA
3- LEER LOS NUMEROS DE TICKETS
a- SE BUSCA EN LA LISTA DE ENTRADAS VENDIDAS
b- SI SE ENCUENTRA SE VAN AGREGANDO A LA COLA.
4- SE CREA LA LISTA POR ZONA
5- SE VAN DESENCOLANDO LOS TICKETS Y SE VAN UBICANDO DE MANERA ORDENADA EN LAS LISTAS CORRESPONDIENTES SEGUN ZONA
ACTIVIDADES
6- CONTAR CANTIDAD DE TICKETS QUE NO ASISTIERON (los que quedaron en la lista)
7- CONTAR CANTIDAD DE TICKETS EN CADA LISTA DE CADA ZONA
8- SACAR EL PORCENTAJE DE ASISTENCIA
9- MOSTRAR CANTIDAD DE ESPECTADORES POR ZONA
*/

//LIBRERIAS
#include <stdio.h> 
#include <stdlib.h>

//TICKET
//Tipo de dato registro
typedef struct Ticket {
    int num;
    char zona;
} Ticket;

//Tipo de dato nodo
typedef struct Nodo {
    Ticket ticket;
    struct Nodo *sig;
} Nodo;

//LISTA DE ENTRADAS VENDIDAS
// Creo la lista con la cabeza
typedef struct Lista {
   Nodo *cabeza;
} Lista;

//COLA DE ESPERA
typedef struct Cola {
   Nodo *cabeza;
   Nodo *ultimo;
} Cola;

//SUBPROGRAMAS

// Funcion CREAR NODO
Nodo *crearNodo(Ticket ticket) {
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo -> ticket = ticket;
    nuevo -> sig = NULL;
    return nuevo;
}

// Funcion PUSH - Inserto al principio
void push(Lista *lista, Ticket ticket) { //pongo a donde pusheo y el tipo de dato
    //creo un nodo con el ticket
    Nodo *nuevo = crearNodo(ticket);
    //insercion al inicio
    nuevo -> sig = lista -> cabeza;
    lista -> cabeza = nuevo;
}

// Funcion encolar - Inserto al final
void encolar(Cola *cola, Ticket ticket) {
    //creo un nodo con el ticket
    Nodo *nuevo = crearNodo(ticket);
    //insercion al final
    if (!cola->cabeza) {  //si la cabeza es null, la cola esta vacia
        cola -> cabeza = nuevo; //el nodo es cabeza y cola
    } else {
        cola -> ultimo -> sig = nuevo;
    }
    cola -> ultimo = nuevo; //el nuevo nodo es el ultimo de la cola
}

// Funcion para poblar la lista
void poblarListaEntradasVendidas(Lista *lista) {
    for (int i=0; i<30; i++) {
        Ticket ticket;
        ticket.num = i+1;
        if (i<10) {
            ticket.zona = 'A';
        } else if (i<20) {
            ticket.zona = 'B';
        } else {
            ticket.zona = 'C';
        }
        //push es la funcion para insertar al inicio de la lista
        push(lista, ticket);
    };
}

//BUSCAR EN LA LISTA Y ELIMINAR EL NODO ENCONTRADO
// Al eliminar el nodo encontrado, la lista queda solo con los tickets NO presentados,
// permitiendo calcular correctamente: asistentes / (asistentes + no asistieron) * 100
char buscarYEliminarDeListaEntradasVendidas(Lista *lista, int num) {
    Nodo *actual = lista->cabeza;
    Nodo *anterior = NULL;

    while (actual) {
        if (actual->ticket.num == num) {
            char zona = actual->ticket.zona;

            // Elimino el nodo de la lista
            if (!anterior) {
                lista->cabeza = actual->sig; // era el primero
            } else {
                anterior->sig = actual->sig; // lo salteo
            }

            free(actual); // libero la memoria
            return zona;
        }
        anterior = actual;
        actual = actual->sig;
    }

    return 'F'; //si no se encuentra el num devuelve F
}

//CREACION DE COLA DE ESPERA
void revisarEntradas(Lista *lista, Cola *cola) {
    int num;

    while(1) {
        printf("Ingrese el numero de ticket (0 para terminar):\n");
        scanf("%d", &num);

        if (num == 0) break; // 0 es la señal de salida

        // Busca en la lista Y elimina el nodo si lo encuentra
        char zona = buscarYEliminarDeListaEntradasVendidas(lista, num);

        if (zona == 'F') {
            printf("Ticket no encontrado \n");
        } else {
            Ticket ticket;
            ticket.num = num;
            ticket.zona = zona;
            //creo el nodo
            encolar(cola, ticket);
            printf("Ticket %d (zona %c).\n", num, zona);
        }
    }
}

//PUSH ORDENADO POR ZONA
void pushOrdenadoPorZona(Lista *lista, Ticket ticket) {
    Nodo *actual = lista->cabeza;
    Nodo *anterior = NULL;
    while (actual && actual->ticket.zona <= ticket.zona) {
        anterior = actual;
        actual = actual->sig;
    }
    // inserción al inicio
    if (!anterior) {
        push(lista, ticket);   // reutiliza tu función
        } else {
            Nodo *nuevo = crearNodo(ticket);
            anterior->sig = nuevo;
            nuevo->sig = actual;
        }
    }

// Recorre la cola sin modificarla y arma la lista ordenada por zona

void cargarListaDesdeCola(Cola *cola, Lista *lista) {
    Nodo *aux = cola->cabeza; // empiezo en el primero de la cola
    while(aux) {
        // inserto el ticket en la lista ordenada por zona
        pushOrdenadoPorZona(lista, aux->ticket);
        aux = aux->sig; // avanzo al siguiente
    }
}

// FUNCION QUE CUENTA LA CANTIDAD DE TICKETS EN LA LISTA DE ENTRADAS VENDIDAS (USAR RECURSIVIDAD)

// FUNCION RECURSIVA que cuenta la cantidad de nodos en una lista
int lengthRec(Nodo *nodo) {

    // caso base
    if (nodo == NULL) {
        return 0;
    }

    // caso recursivo
    return 1 + lengthRec(nodo->sig);
}

// FUNCION RECURSIVA que cuenta la cantidad de tickets de cada zona
void contarZonasRec(Nodo *nodo, int *za, int *zb, int *zc) {
    // caso base: si el nodo es NULL, no hay más elementos para contar
    if (nodo == NULL) {
        return;
    }

    // Evaluamos la zona del ticket del nodo actual
    switch (nodo->ticket.zona) {
        case 'A': (*za)++;  // sumo 1 al contador de zona A
            break;
        case 'B': (*zb)++;  // sumo 1 al contador de zona B
            break;
        case 'C': (*zc)++;  // sumo 1 al contador de zona C
            break;
    }

    // Llamada recursiva avanzando al siguiente nodo
    contarZonasRec(nodo->sig, za, zb, zc);
}



int main() {
    
    // 1- GENERAR LA LISTA DE ENTRADAS VENDIDAS
    Lista entradasVendidas = {NULL}; //creo la lista vacia
    poblarListaEntradasVendidas(&entradasVendidas); //uso la funcion para poblar la lista

    // 2- SE CREA UNA COLA DE ESPERA
    Cola cola = {NULL, NULL};
    // 3- LEER LOS NUMEROS DE TICKETS
    // Cada ticket encontrado se ELIMINA de la lista de vendidos y se encola.
    // Al terminar, entradasVendidas solo contiene los tickets que NO se presentaron.
    revisarEntradas(&entradasVendidas, &cola);

    // 4- SE CREA LA LISTA POR ZONA
    Lista listaOrdenadaPorZona = {NULL};
    // 5- SE VAN PASANDO LOS TICKETS Y SE VAN UBICANDO DE MANERA ORDENADA EN LA LISTA SEGUN ZONA A<B<C
    cargarListaDesdeCola(&cola, &listaOrdenadaPorZona);

    // 6- CONTAR CANTIDAD DE TICKETS QUE NO ASISTIERON (los que quedaron en la lista)
    // Como se eliminaron los encontrados, lo que queda son los ausentes
    int noAsistieron = lengthRec(entradasVendidas.cabeza);

    // 7- CONTAR CANTIDAD DE TICKETS DE CADA ZONA (USAR RECURSIVIDAD)
    int totalZA = 0;
    int totalZB = 0;
    int totalZC = 0;
    contarZonasRec(listaOrdenadaPorZona.cabeza, &totalZA, &totalZB, &totalZC);

    // 8- SACAR EL PORCENTAJE DE ASISTENCIA.
    // cantidad de tickets vendidos: totalEntradasVendidas
    // cantidad de espectadores que ingresaron:
    int totalAsistentes = totalZA + totalZB + totalZC; 
    int totalVendidos = totalAsistentes + noAsistieron; // reconstruimos el total original
    float porcentaje = ((float)totalAsistentes / totalVendidos) * 100;

    // 9- MOSTRAR RESULTADOS

    printf("\n--- RESULTADOS ---\n");
    printf("Total entradas vendidas: %d\n", totalVendidos);
    printf("Total asistentes: %d\n", totalAsistentes);
    printf("Porcentaje de asistencia total: %.2f %%\n", porcentaje);
    printf("Total de asistencias en zona A: %d \n", totalZA);
    printf("Total de asistencias en zona B: %d \n", totalZB);
    printf("Total de asistencias en zona C: %d \n", totalZC);

    return 0;

}