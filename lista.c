#include "lista.h"
#include <stdio.h>
#include <stdlib.h>


/* Definición del struct nodo*/
typedef struct nodo{
        void* dato;
        struct nodo* siguiente;
} nodo_t;

/* Definición del struct lista*/
struct lista{
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

/* Definición del struct lista_iter*/
struct lista_iter {
	lista_t* lista;
	struct nodo* act;
	struct nodo* ant;
};

/* ******************************************************************
 *                FUNCIONES AUXILIARES PARA NODOS
 * *****************************************************************/

nodo_t* crear_nodo(void);
void destruir_nodo(nodo_t* nodo);

nodo_t* crear_nodo(void) {
    nodo_t* nodo= malloc(sizeof(nodo_t));
    if (nodo == NULL) {
        return NULL;
    }
    nodo->dato = NULL;
    nodo->siguiente = NULL;
    return nodo;
}

void destruir_nodo(nodo_t* nodo) {
    free(nodo);
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t *lista_crear(void) {
    lista_t* lista = malloc(sizeof(lista_t));
    if (lista == NULL) {
        return lista;
    }

    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
    if (lista->largo == 0 && lista->primero == NULL && lista->ultimo == NULL) {
        return true;
    }
    return false;
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t* nodo_nuevo = crear_nodo();
    if (nodo_nuevo == NULL) {
        return false;
    }

    nodo_nuevo->dato = dato;

    if (lista->primero == NULL && lista->ultimo == NULL) {
        lista->primero = nodo_nuevo;
        lista->ultimo  = nodo_nuevo;
    } else {
        nodo_nuevo->siguiente = lista->primero;
        lista->primero = nodo_nuevo;
    }
    lista->largo++;
    return true;

}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t* nodo_nuevo = crear_nodo();
    if (nodo_nuevo == NULL) {
        return false;
    }

    nodo_nuevo->dato = dato;

    if (lista->primero == NULL && lista->ultimo == NULL) {
        lista->primero = nodo_nuevo;
        lista->ultimo  = nodo_nuevo;
    } else {
        lista->ultimo->siguiente = nodo_nuevo;
        lista->ultimo = nodo_nuevo;
    }

    nodo_nuevo->siguiente = NULL;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    nodo_t* primer_nodo = lista->primero;
    void* valor = primer_nodo->dato;

    if (primer_nodo->siguiente == NULL) {
        lista->primero = NULL;
        lista->ultimo = NULL;
    } else {
        lista->primero = primer_nodo->siguiente;
    }

    lista->largo--;
    destruir_nodo(primer_nodo);
    return valor;
}

void *lista_ver_primero(const lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista) {
    size_t largo = lista->largo;
    return largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    while (!lista_esta_vacia(lista)) {
        void* elemento_eliminado = lista_borrar_primero(lista);
         if (destruir_dato != NULL){
            destruir_dato(elemento_eliminado);
        }
    }
    free(lista);    
    return;
}

/* *****************************************************************
 *               PRIMITIVA DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    if (lista_esta_vacia(lista)) {
        return;
    }

    bool continuar = true;
    nodo_t* actual = lista->primero;
    
    while (actual && continuar) {

        continuar = visitar(actual->dato, extra);
        actual = actual->siguiente;
    }

    return;
}

/* *****************************************************************
 *               PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if(iter == NULL){
        return NULL;
    }
    iter->lista = lista;
    iter->act = lista->primero;
    iter->ant = NULL;

    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    // Si la lista esta vacia no se puede avanzar
    if(lista_esta_vacia(iter->lista)) {
        return false;
    }

    // Si el iterador se encuentra al final, no se puede avanzar
    if(lista_iter_al_final(iter)) {
        return false;
    }

    iter->ant = iter->act;
    iter->act = iter->act->siguiente;

    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if(lista_esta_vacia(iter->lista)) {
        return NULL;
    }

    // Si el iterador esta al final, devuelvo el valor del anterior
    if(lista_iter_al_final(iter)) {
        return iter->ant->dato;
    }

    return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    return (iter->act == NULL);
}

void lista_iter_destruir(lista_iter_t *iter) {
    iter->lista = NULL;
    iter->act = NULL;
    iter->ant = NULL;
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t* nodo_nuevo = crear_nodo();
    if(nodo_nuevo == NULL) {
        return false;
    }
    nodo_nuevo->dato = dato;
    nodo_nuevo->siguiente = iter->act;

    // Lista vacia, inserto y cambio los punteros (primero y ultimo) de la lista
    if(lista_esta_vacia(iter->lista)) {
        iter->lista->primero = nodo_nuevo;
        iter->lista->ultimo = nodo_nuevo;
        iter->act = nodo_nuevo;
        iter->lista->largo++;
        return true;
    }

    // Si el iterador esta al final, inserto y cambio el puntero ultimo de la lista
    if(lista_iter_al_final(iter)) {
        iter->act = nodo_nuevo;
        iter->ant->siguiente = iter->act;
        iter->lista->ultimo = nodo_nuevo;
        iter->lista->largo++;
        return true;
    }

    // Si el iterador esta en la primer posicion, inserto y cambio el puntero primero de la lista
    if(iter->act == iter->lista->primero) {
        iter->lista->primero = nodo_nuevo;
        iter->act = nodo_nuevo;
        iter->lista->largo++;
        return true;
    }

    // En otro caso el iterador no se encuentra ni al principio ni al final de la lista
    iter->ant->siguiente = nodo_nuevo;
    iter->act = nodo_nuevo;
    iter->lista->largo++;

    return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
    if(lista_esta_vacia(iter->lista)) {
        return NULL;
    }

    // Si el iterador se encuentra al final de la lista (NULL)
    if(lista_iter_al_final(iter)) {
        return NULL;
    }

    void* aux = iter->act->dato;
    nodo_t* nodo_eliminar = iter->act;

    // Si la lista tiene solo 1 elemento
    if(iter->lista->largo == 0) {
        iter->lista->ultimo = NULL;
        iter->lista->primero = NULL;
        iter->act = NULL;
        destruir_nodo(nodo_eliminar);
        iter->lista->largo--;
        return aux;
    }

    // Si el iterador se encuentra en el ultimo elemento de la lista
    if(iter->act == iter->lista->ultimo) {
        iter->lista->ultimo = iter->ant;
        iter->ant->siguiente = iter->act->siguiente;
        iter->act = iter->act->siguiente;
        destruir_nodo(nodo_eliminar);
        iter->lista->largo--;
        return aux;
    }

    // Si el iterador se encuentra al principio de la lista
    if(iter->act == iter->lista->primero){
        iter->act = iter->act->siguiente;
        iter->lista->primero = iter->act;
        destruir_nodo(nodo_eliminar);
        iter->lista->largo--;
        return aux;
    }


    // En otro caso el iterador se encuentra entre (sin incluir) el principio - final
    iter->act = iter->act->siguiente;
    iter->ant->siguiente = iter->act;
    destruir_nodo(nodo_eliminar);
    iter->lista->largo--;
    return aux;
}