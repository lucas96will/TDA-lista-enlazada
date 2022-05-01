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
    iter->act = lista_ver_primero(lista);
    iter->ant = NULL;

    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    //Si la lista esta vacia no se puede avanzar
    if(lista_esta_vacia(iter->lista)) {
        return false;
    }

    //Si el iterador se encuentra al final, no se puede avanzar
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

    //Si el iterador esta al final, devuelvo el valor del anterior
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

bool lista_iter_insertar(lista_iter_t *iter, void *dato);

void *lista_iter_borrar(lista_iter_t *iter);