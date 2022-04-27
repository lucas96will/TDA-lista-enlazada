#include "lista.h"

/* Definición del struct nodo*/
typedef stuct nodo{
        void* dato;
        struct nodo* siguiente;
} nodo_t;

/* Definición del struct lista*/
struct lista{
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};