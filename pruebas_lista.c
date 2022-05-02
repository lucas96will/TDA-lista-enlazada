#include <stdio.h>
#include "lista.h"
#include "testing.h"
#include "pila.h"

#define TAM_PRUEBA_VEC 5
#define TAM_PRUEBA_VOLUMEN 100



/*Funcion para agregar todos los elementos del arreglo vec usando insertar (puede elegirse al principio o ultimo)*/
void _lista_insertar_arreglo(lista_t* lista, int* vec, size_t largo, bool insertar(lista_t* lista, void* dato)) {
    for(int i = 0; i < largo; i++) {
        insertar(lista, &vec[i]);
    }
}

/*borra todos los valores de la lista(de enteros) y compara con los valores del arreglo (ascendente)*/
bool _lista_borrar_comparar(lista_t* lista, const int* vec) {
    int num;
    size_t i = 0;
    while(!lista_esta_vacia(lista)) {
        num = *(int*)lista_borrar_primero(lista);
        if(num != vec[i++]){
            return false;
        }
    }
    return true;
}

static void prueba_lista_crear() {
    lista_t* lista = lista_crear();
    printf("\nINICIO DE PRUEBAS DE CREAR LISTA\n");
    print_test("Crear lista", lista != NULL);
    print_test("Lista creada vacia", lista_esta_vacia(lista));
    print_test("Lista creada borrar primero es NULL", lista_borrar_primero(lista) == NULL);
    print_test("Lista creada ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista creada ver ultimo es NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista creada obtener largo es 0", lista_largo(lista) == 0);

    //Inserto un elemento y lo borro
    int num = 8;
    lista_insertar_primero(lista,&num);
    lista_borrar_primero(lista);

    printf("\nInserto un elemento y lo borro, pruebo si la pila se comporta como recien creada\n");
    print_test("Lista vacia", lista_esta_vacia(lista));
    print_test("Lista borrar primero es NULL", lista_borrar_primero(lista) == NULL);
    print_test("Lista ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista ver ultimo es NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista obtener largo es 0", lista_largo(lista) == 0);


    lista_destruir(lista, NULL);
}
static void prueba_lista_insertar() {
    printf("\nINICIO DE PRUEBAS DE LISTA INSERTAR\n");

    lista_t* lista = lista_crear();
    int vec[TAM_PRUEBA_VEC] = {2, 4, 6, 8, 10};

    //Inserto el 2 al princpio y pruebo si el primero es 2
    print_test("Insertar el 2 primero en la lista", lista_insertar_primero(lista, &vec[0]));
    print_test("El primero en la lista es el 2", *(int*) lista_ver_primero(lista) == 2);

    //Inserto el 4 al princpio y pruebo si el primero es 4, el ultimo 2
    print_test("Insertar el 4 primero en la lista", lista_insertar_primero(lista, &vec[1]));
    print_test("El primero en la lista es el 4", *(int*) lista_ver_primero(lista) == 4);
    print_test("Ultimo en la lista es el 2", *(int*) lista_ver_ultimo(lista) == 2);

    //Inserto el 6 al principio y pruebo si el primero es 6 y ultimo 2
    print_test("Insertar el 6 primero en la lista", lista_insertar_primero(lista, &vec[2]));
    print_test("El primero en la lista es el 6", *(int*) lista_ver_primero(lista) == 6);
    print_test("Ultimo en la lista es el 2", *(int*) lista_ver_ultimo(lista) == 2);

    //Inserto el 8 a lo ultimo y pruebo si el primero es 6 y el ultimo 8
    print_test("Insertar el 6 primero en la lista", lista_insertar_ultimo(lista, &vec[3]));
    print_test("El primero en la lista es el 6", *(int*) lista_ver_primero(lista) == 6);
    print_test("Ultimo en la lista es el 8", *(int*) lista_ver_ultimo(lista) == 8);

    //Inserto el 10 a lo ultimo y pruebo si el primero es 6 y el ultimo 10
    print_test("Insertar el 6 primero en la lista", lista_insertar_ultimo(lista, &vec[4]));
    print_test("El primero en la lista es el 6", *(int*) lista_ver_primero(lista) == 6);
    print_test("Ultimo en la lista es el 8", *(int*) lista_ver_ultimo(lista) == 10);

    lista_destruir(lista, NULL);
}

static void prueba_lista_esta_vacia() {
    printf("\nINICIO DE PRUEBAS DE LISTA ESTA VACIA\n");

    int vec[TAM_PRUEBA_VEC] = {2, 4, 6, 8, 10};
    lista_t* lista = lista_crear();

    //Inserto al principio, pruebo si esta vacia
    print_test("Insertar el 2, primero en la lista", lista_insertar_primero(lista, &vec[0]));
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));

    //borro al principio y pruebo si esta vacia
    print_test("Borro el 2 de la lista", *(int*) lista_borrar_primero(lista) == 2);
    print_test("La lista esta vacia", lista_esta_vacia(lista));

    //Inserto a lo ultimo, pruebo si esta vacia
    print_test("Insertar el 2, ultimo en la lista", lista_insertar_ultimo(lista, &vec[0]));
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));

    //borro al principio y pruebo si esta vacia
    print_test("Borro el 2 de la lista", *(int*) lista_borrar_primero(lista) == 2);
    print_test("La lista esta vacia", lista_esta_vacia(lista));


    lista_destruir(lista, NULL);
}



static void prueba_lista_borrar() {
    printf("\nINICIO DE PRUEBAS DE LISTA BORRAR\n");

    int vec[TAM_PRUEBA_VEC] = {4, 8, 12, 16, 20};
    int vec2[TAM_PRUEBA_VEC] = {20, 16, 12, 8, 4};
    lista_t* lista = lista_crear();

    //Agrego a la lista algunos elementos a lo ultimo
    _lista_insertar_arreglo(lista, vec, TAM_PRUEBA_VEC, lista_insertar_ultimo);
    //La lista deberia ser (primero) [4, 8, 12, 16, 20] (ultimo), comprobamos*/

    //Pruebo si los elementos borrados son los correctos!
    print_test("Prueba lista borrar elementos agregados al final", _lista_borrar_comparar(lista, vec));

    //Agrego elementos al principio y compruebo que al borrar sean los adecuados
    _lista_insertar_arreglo(lista, vec, TAM_PRUEBA_VEC, lista_insertar_primero);
    //La lista deberia ser (primero) [20, 16, 12, 8, 4] (ultimo), comprobamos*/

    print_test("Prueba lista borrar elementos agregados al principio", _lista_borrar_comparar(lista, vec2));

    lista_destruir(lista, NULL);
}

static void prueba_lista_largo() {
    lista_t* lista = lista_crear();
    int vec[TAM_PRUEBA_VEC] = {4, 8, 12, 16, 20};

    printf("\nINICIO DE PRUEBAS DE LARGO DE LISTA\n");

    print_test("Prueba largo lista recien creada es 0", lista_largo(lista) == 0);

    //Inserto 1 elemento y pruebo si el largo es 1
    lista_insertar_primero(lista, &vec[0]);
    print_test("Inserto un elemento, largo de lista 1", lista_largo(lista) == 1);

    //Borro el dato y pruebo si el largo es 0
    lista_borrar_primero(lista);
    print_test("Borro el unico elemento, largo de lista 0", lista_largo(lista) == 0);

    //Inserto varios elementos y pruebo si el largo es correcto
    _lista_insertar_arreglo(lista, vec, TAM_PRUEBA_VEC, lista_insertar_primero);
    print_test("Inserto 5 elementos, largo de lista 5", lista_largo(lista) == 5);

    //Borro 1 elemento y pruebo si el largo es 4
    lista_borrar_primero(lista);
    print_test("Borro 1 elemento, largo de lista 4", lista_largo(lista) == 4);

    //Borro todos los elementos y pruebo si el largo es 0
    while(!lista_esta_vacia(lista)) {
        lista_borrar_primero(lista);
    }
    print_test("Borro todos los elementos, largo de lista es 0", lista_largo(lista) == 0);

    lista_destruir(lista, NULL);
}

static void prueba_lista_ver() {
    lista_t* lista = lista_crear();
    int vec[TAM_PRUEBA_VEC] = {4, 8, 12, 16, 20};

    printf("\nINICIO DE PRUEBAS DE LISTA VER PRIMERO / ULTIMO \n");

    lista_insertar_primero(lista, &vec[0]);
    print_test("Inserto al inicio el 4 en la lista y el primero es el 4", *(int*) lista_ver_primero(lista) == 4);
    print_test("El ultimo en la lista es el 4", *(int*) lista_ver_ultimo(lista) == 4);

    lista_insertar_primero(lista, &vec[1]);
    print_test("Inserto al inicio el 8 en la lista y el primero es el 8", *(int*) lista_ver_primero(lista) == 8);
    print_test("El ultimo en la lista es el 4", *(int*) lista_ver_ultimo(lista) == 4);

    lista_insertar_ultimo(lista, &vec[2]);
    print_test("Inserto al final el 12 en la lista y el primero es el 8", *(int*) lista_ver_primero(lista) == 8);
    print_test("El ultimo en la lista es el 12", *(int*) lista_ver_ultimo(lista) == 12);

    //La lista es [8, 4, 12]

    //Borro y me voy fijando el primero

    lista_borrar_primero(lista);
    print_test("Borro el primer elemento de la lista y el nuevo primero es el 4", *(int*) lista_ver_primero(lista) == 4);
    print_test("El ultimo elemento sigue siendo el 12", *(int*) lista_ver_ultimo(lista) == 12);

    lista_borrar_primero(lista);
    print_test("Borro el primer elemento de la lista y el nuevo primero es el 4", *(int*) lista_ver_primero(lista) == 12);
    print_test("El ultimo elemento sigue siendo el 12", *(int*) lista_ver_ultimo(lista) == 12);

    lista_borrar_primero(lista);
    //ambos, ultimo y primero deben ser null
    print_test("El primer elemento de la lista es null", lista_ver_primero(lista) == NULL);
    print_test("El ultimo elemento de la lista es null", lista_ver_ultimo(lista) == NULL);

    lista_destruir(lista, NULL);
}

static void prueba_lista_NULL() {
    printf("\nINICIO DE PRUEBAS DE VOLUMEN PARA LISTA \n");

    lista_t* lista = lista_crear();
    print_test("Lista esta vacia", lista_esta_vacia(lista));
    print_test("Inserto NULL al principio", lista_insertar_primero(lista, NULL));
    print_test("Inserto NULL al final", lista_insertar_ultimo(lista, NULL));
    print_test("El primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("El ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("Borrar el primero devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("Borrar el primero devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("Lista esta vacia nuevamente", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
}

static void prueba_lista_volumen() {
    printf("\nINICIO DE PRUEBAS DE VOLUMEN PARA LISTA \n");

    size_t tam = 5000;
    size_t i = 0;
    bool ok_insertar = true;
    bool ok_primero = true;
    bool ok_ultimo = true;
    bool ok_borrar = true;

    lista_t* lista = lista_crear();

    for (;i < tam; i++) {
        ok_insertar &= lista_insertar_ultimo(lista, &i);
        ok_ultimo &= (lista_ver_ultimo(lista) == &i);
    }

    i = 0;
    print_test("Se pudieron insertar todos los elementos", ok_insertar);
    print_test("Todos los ultimos eran correctos", ok_ultimo);

    for (;i < tam; i++) {
        ok_primero &= (lista_ver_primero(lista) == &i);
        ok_borrar &= (lista_borrar_primero(lista) == &i);
    }

    print_test("Se pudieron borrar todos los elementos", ok_borrar);
    print_test("Todos los primeros eran correctos", ok_primero);

    lista_destruir(lista, NULL);

}

static void prueba_lista_vacia_destruccion_con_free() {
    lista_t* lista = lista_crear();

    printf("\nINICIO DE PRUEBAS DE DESTRUCCION CON LISTA VACIA Y FREE \n");

    print_test("Crear lista", lista != NULL);
    print_test("Lista creada vacia", lista_esta_vacia(lista));
    print_test("Lista creada borrar primero es NULL", lista_borrar_primero(lista) == NULL);
    print_test("Lista creada ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista creada ver ultimo es NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista creada obtener largo es 0", lista_largo(lista) == 0);

    lista_destruir(lista, free);
}

//Creo Wrapper para que cumplir la firma de lista_destruir
void pila_destruir_wrapper(void* pila);

void pila_destruir_wrapper(void* pila) {
    pila_destruir(pila);
}

static void prueba_lista_de_pilas_con_destruccion() {
    lista_t* lista = lista_crear();

    printf("\nINICIO DE PRUEBAS DE DESTRUCCION CON LISTA DE PILAS \n");

    int num1 = 1, num2 = 2, num3 = 3;
    
    //Creo 3 pilas distintas
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();

    //Dos pilas tendran elementos, otra no
    pila_apilar(pila2, &num1);
    pila_apilar(pila2, &num2);
    pila_apilar(pila3, &num3);

    print_test("Inserto pila 1 en primer posicion", lista_insertar_primero(lista, pila1));
    print_test("Pila 1 es el primero", lista_ver_primero(lista) == pila1);
    print_test("Inserto pila 2 en primer posicion", lista_insertar_primero(lista, pila2));
    print_test("Pila 2 es el primero", lista_ver_primero(lista) == pila2);
    print_test("Inserto pila 3 en primer posicion", lista_insertar_primero(lista, pila3));
    print_test("Pila 3 es el primero", lista_ver_primero(lista) == pila3);
    
    print_test("Pila 1 es el ultimo", lista_ver_ultimo(lista) == pila1);

    lista_destruir(lista, pila_destruir_wrapper);
}

static void prueba_lista_de_pilas_con_destruccion_manual() {
    lista_t* lista = lista_crear();

    printf("\nINICIO DE PRUEBAS DE DESTRUCCION CON LISTA DE PILAS Y DESTRUCCION MANUAL \n");

    int num1 = 1, num2 = 2, num3 = 3;
    
    //Creo 3 pilas distintas
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();

    //Dos pilas tendran elementos, otra no
    pila_apilar(pila2, &num1);
    pila_apilar(pila2, &num2);
    pila_apilar(pila3, &num3);

    print_test("Inserto pila 1 en primer posicion", lista_insertar_primero(lista, pila1));
    print_test("Pila 1 es el primero", lista_ver_primero(lista) == pila1);
    print_test("Inserto pila 2 en primer posicion", lista_insertar_primero(lista, pila2));
    print_test("Pila 2 es el primero", lista_ver_primero(lista) == pila2);
    print_test("Inserto pila 3 en primer posicion", lista_insertar_primero(lista, pila3));
    print_test("Pila 3 es el primero", lista_ver_primero(lista) == pila3);
    
    print_test("Pila 1 es el ultimo", lista_ver_ultimo(lista) == pila1);

    lista_destruir(lista, NULL);

    //Destruyo manualmente las pilas utilizadas
    pila_destruir(pila1);
    pila_destruir(pila2);
    pila_destruir(pila3);
}


bool sumar_numero(void* dato, void* sumar) {
    *(int*) dato += *(int*) sumar;
    return true;
}

typedef struct num_iterador{
    bool estado;
    int num;
} num_iterador_t;

bool encontrar_numero(void* dato, void* encontrado){
    num_iterador_t aux = *(num_iterador_t*) encontrado;
    if(*(int*) dato == aux.num){
        aux.estado = true;
        *(num_iterador_t*) encontrado = aux;
        return false;
    }
    return true;
}

bool sumar_primeros_5(void* dato, void* extra){
    if(*(int*) dato == 5){
        return false;
    }
    *(int*) extra += *(int*) dato;
    return true;
}

void static prueba_lista_iterar_interno() {
    lista_t* lista = lista_crear();
    int* vec = malloc(TAM_PRUEBA_VOLUMEN*sizeof(int));

    //Inserto los elementos a la lista
    for(int i = 0; i < TAM_PRUEBA_VOLUMEN; i++) {
        vec[i] = i;
        lista_insertar_ultimo(lista, &vec[i]);
    }

    int numero_a_sumar = 1;
    lista_iterar(lista, sumar_numero, &numero_a_sumar);


    num_iterador_t num_a_encontrar;
    num_a_encontrar.estado = false;
    num_a_encontrar.num = 99;

    //Hallo si el 99 esta en la lista

    lista_iterar(lista, encontrar_numero, &num_a_encontrar);

    print_test("Se hallo el 99 en la lista con iterador interno", num_a_encontrar.estado);

    bool suma = true;
    int j = 0;
    int num_aux;
    while(!lista_esta_vacia(lista)) {
        num_aux = *(int*) lista_borrar_primero(lista);
        suma &= (num_aux == j+1);
        j++;
    }

    print_test("Sumo 1 a todos los elementos con iterador interno", suma);

    _lista_insertar_arreglo(lista, vec, TAM_PRUEBA_VOLUMEN, lista_insertar_ultimo);

    int sumas = 0;

    lista_iterar(lista, sumar_primeros_5, &sumas);

    print_test("Sumo los primeros 5 elementos", sumas == 10);

    while(!lista_esta_vacia(lista)){
        lista_borrar_primero(lista);
    }

    print_test("Borro todos los elementos de la lista", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
    free(vec);
}

static void prueba_iterador_externo_operaciones_basicas() {

    printf("\nINICIO DE PRUEBAS DE ITERADOR EXTERNO CREAR, VER ACTUAL, ITER AL FINAL, AVANZAR \n");

    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);

    print_test("El iterador fue creado", iter != NULL);
    print_test("Ver actual del iterador en una lista vacia es null", lista_iter_ver_actual(iter) == NULL);
    print_test("El iterador se encuentra al final de la lista", lista_iter_al_final(iter));
    print_test("Avanzar el iterador no es posible y devuelve false", lista_iter_avanzar(iter) == false);


    int vec[TAM_PRUEBA_VEC] = {4, 8, 12, 16, 20};
    lista_iter_insertar(iter, &vec[0]);
    // Primer elemento de la lista es 4

    print_test("Inserto con iterador el 4 en la primera posicion de la lista", *(int*) lista_ver_primero(lista) == 4);
    print_test("Ver actual del iterador devuelve el 4", *(int*) lista_iter_ver_actual(iter) == 4);
    print_test("El iterador no se encuentra al final de la lista", lista_iter_al_final(iter) == false);
    // Avanzo el iterador
    print_test("Avanzar el iterador es posible", lista_iter_avanzar(iter));
    print_test("El iterador se encuentra al final", lista_iter_al_final(iter));

    // Inserto el 8 -> [4, 8]
    lista_iter_insertar(iter, &vec[1]);
    print_test("Inserto el 8 y ver actual del iterador devuelve un 8", *(int*) lista_iter_ver_actual(iter) == 8);
    print_test("El iterador no se encuentra al final", lista_iter_al_final(iter) == false);
    print_test("Avanzar el iterador es posible", lista_iter_avanzar(iter));
    print_test("El iterador se encuentra al final", lista_iter_al_final(iter));
    print_test("Avanzar el iterador al final no es posible", lista_iter_avanzar(iter) == false);
    print_test("Borrar con el iterador al final no es posible", lista_iter_borrar(iter) == false);

    lista_iter_destruir(iter);

    print_test("Destruyo el iterador y la lista no esta vacia", lista_esta_vacia(lista) == false);
    print_test("Destruyo el iterador y el primero en la lista es el 4", *(int*) lista_ver_primero(lista) == 4);
    print_test("Destruyo el iterador y el ultimo en la lista es el 8", *(int*) lista_ver_ultimo(lista) == 8);

    // Borro los elementos con el iterador
    lista_iter_t *aux = lista_iter_crear(lista);
    lista_iter_borrar(aux);
    print_test("Borro un elemento con el iterador y la lista no esta vacia", lista_esta_vacia(lista) == false);
    print_test("El ultimo de la lista es el 8", *(int*) lista_ver_ultimo(lista) == 8);
    print_test("El primero de la lista es el 4", *(int*) lista_ver_primero(lista) == 8);

    lista_iter_borrar(aux);
    print_test("Borro un elemento con el iterador y la lista esta vacia", lista_esta_vacia(lista));
    print_test("Ver ultimo de la lista es null", lista_ver_ultimo(lista) == NULL);
    print_test("Ver primero de la lista es null", lista_ver_ultimo(lista) == NULL);


    lista_iter_destruir(aux);
    lista_destruir(lista, NULL);
}

static void pruebas_iterador_externo_insertar() {
    
    printf("\nINICIO DE PRUEBAS DE INSERTAR CON ITERADOR EXTERNO \n");

    lista_t* lista = lista_crear();

    int vec[TAM_PRUEBA_VEC] = {4, 8, 12, 16, 20};

    print_test("Inserto al 12 como primero de la lista", lista_insertar_primero(lista, &vec[2]));
    print_test("Inserto al 16 como ultimo de la lista", lista_insertar_ultimo(lista, &vec[3]));
    //La lista es [12, 16]

    lista_iter_t* iter = lista_iter_crear(lista);

    print_test("Inserto al 4 como primero de la lista usando el iterador", lista_iter_insertar(iter, &vec[0]));
    print_test("Verifico que el actual sea el 4", *(int*) lista_iter_ver_actual(iter) == 4);
    print_test("Verifico que el primero de la lista sea el 4", *(int*) lista_ver_primero(lista) == 4);
    //La lista es [4, 12, 16]

    lista_iter_avanzar(iter);

    print_test("Inserto al 8 en el medio de la lista usando el iterador", lista_iter_insertar(iter, &vec[1]));
    print_test("Verifico que el actual sea el 8", *(int*) lista_iter_ver_actual(iter) == 8);
    //La lista es [4, 8, 12, 16]

    while (!lista_iter_al_final(iter)) {
        lista_iter_avanzar(iter);
    }

    print_test("El iterador esta al final", lista_iter_al_final(iter));
    print_test("Inserto al 20 como ultimo de la lista usando el iterador", lista_iter_insertar(iter, &vec[4]));
    print_test("Verifico que el actual sea el 20", *(int*) lista_iter_ver_actual(iter) == 20);
    print_test("Verifico que el utlimo de la lista es el 20", *(int*) lista_ver_ultimo(lista) == 20);
    //La lista es [4, 8, 12, 16, 20]

    //Si inserto un elemento ahora sera antes al 20 -> lista: [4, 8, 12, 16, 18, 20]

    int nuevo = 18;
    print_test("El iterador no esta al final", !lista_iter_al_final(iter));
    print_test("Inserto al 18 como anteultimo de la lista usando el iterador", lista_iter_insertar(iter, &nuevo));
    print_test("Verifico que el actual sea el 18", *(int*) lista_iter_ver_actual(iter) == 18);
    print_test("verifico que el utlimo de la lista es el 20 igualmente", *(int*) lista_ver_ultimo(lista) == 20);
    //La lista es [4, 8, 12, 16, 18, 20] ->largo = 6

    lista_iter_destruir(iter);
    //Verifico que despues de destruido el iterador la lista no pierde los cambios hechos con este
    print_test("El primero es el 4", *(int*) lista_ver_primero(lista) == 4);
    print_test("El ultimo es el 20", *(int*) lista_ver_ultimo(lista) == 20);
    print_test("El largo es 6", lista_largo(lista) == 6);

    //Hallo si el 18 esta en la lista
    num_iterador_t num_a_encontrar;
    num_a_encontrar.estado = false;
    num_a_encontrar.num = 18;
    lista_iterar(lista, encontrar_numero, &num_a_encontrar);

    print_test("Se hallo el 18 en la lista con iterador interno", num_a_encontrar.estado);

    //Destruyo la lista
    lista_destruir(lista, NULL);    
}

static void pruebas_iterador_externo_borrar() {
    
    printf("\nINICIO DE PRUEBAS DE BORRAR CON ITERADOR EXTERNO \n");

    lista_t* lista = lista_crear();
    int vec[TAM_PRUEBA_VEC] = {4, 8, 12, 16, 20};
    
    lista_insertar_primero(lista, &vec[0]);
    lista_insertar_ultimo(lista, &vec[1]);
    lista_insertar_ultimo(lista, &vec[2]);
    lista_insertar_ultimo(lista, &vec[3]);
    lista_insertar_ultimo(lista, &vec[4]);

    print_test("El primero de la lista es el 4", *(int*) lista_ver_primero(lista) == 4);
    print_test("El ultimo de la lista es el 20", *(int*)lista_ver_ultimo(lista) == 20);
    print_test("El largo de la lista es 5", lista_largo(lista) == 5);
    //La lista es [4, 8, 12, 16, 20]

    lista_iter_t* iter = lista_iter_crear(lista);

    print_test("Elimino al 4", *(int*) lista_iter_borrar(iter) == 4);
    print_test("El actual para el iterador es el 8", *(int*) lista_iter_ver_actual(iter) == 8);
    print_test("El primero de la lista es el 8", *(int*) lista_ver_primero(lista) == 8);
    //La lista es [8, 12, 16, 20]

    lista_iter_avanzar(iter);
    print_test("Elimino al 12", *(int*) lista_iter_borrar(iter) == 12);
    print_test("El actual para el iterador es el 16", *(int*) lista_iter_ver_actual(iter) == 16);
    //La lista es [8, 16, 20]

    lista_iter_avanzar(iter);
    print_test("Elimino al 20", *(int*) lista_iter_borrar(iter) == 20);
    print_test("El actual para el iterador es NULL", lista_iter_ver_actual(iter) == NULL);

    print_test("El iterador esta al final", lista_iter_al_final(iter));
    print_test("Eliminar no cambia nada", lista_iter_borrar(iter) == NULL);
    print_test("El actual para el iterador es NULL", lista_iter_ver_actual(iter) == NULL);
    //La lista es [8, 16]: largo -> 2

    lista_iter_destruir(iter);

    //Verifico que despues de destruido el iterador la lista no pierde los cambios hechos con este
    print_test("El primero es el 8", *(int*) lista_ver_primero(lista) == 8);
    print_test("El ultimo es el 16", *(int*) lista_ver_ultimo(lista) == 16);
    print_test("El largo es 2", lista_largo(lista) == 2);

    //Hallo si el 18 esta en la lista
    num_iterador_t num_a_encontrar;
    num_a_encontrar.estado = false;
    num_a_encontrar.num = 12;
    lista_iterar(lista, encontrar_numero, &num_a_encontrar);

    print_test("No se hallo el 12 en la lista con iterador interno", !num_a_encontrar.estado);

    //Destruyo la lista
    lista_destruir(lista, NULL); 

}

static void pruebas_iterador_externo_NULL() {
    
    printf("\nINICIO DE PRUEBAS DE LISTA CON NULL E ITERADOR EXTERNO \n");

    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);

    print_test("Lista esta vacia", lista_esta_vacia(lista));

    print_test("Inserto un NULL con el iterador", lista_iter_insertar(iter, NULL));
    print_test("Inserto un NULL con el iterador", lista_iter_insertar(iter, NULL));
    print_test("Inserto un NULL con el iterador", lista_iter_insertar(iter, NULL));
    //Lista es [NULL, NULL, NULL] -> largo 3
    
    print_test("Lista no esta vacia", !lista_esta_vacia(lista));
    print_test("Elimino el primer NULL", lista_iter_borrar(iter) == NULL);
    //Lista es [NULL, NULL] -> largo 2

    lista_iter_avanzar(iter);

    print_test("Elimino el ultimo NULL", lista_iter_borrar(iter) == NULL);
    //Lista es [NULL] -> largo 1
    print_test("El actual para el iterador es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("El primero de la lista es NULL",lista_ver_primero(lista) == NULL);
    print_test("El ultimo de la lista es NULL",lista_ver_ultimo(lista) == NULL);
    print_test("El largo de la lista es 1", lista_largo(lista) == 1);
    print_test("Lista no esta vacia", !lista_esta_vacia(lista));

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

void pruebas_lista_estudiante() {

    prueba_lista_crear();
    prueba_lista_esta_vacia();
    prueba_lista_insertar();
    prueba_lista_borrar();
    prueba_lista_largo();
    prueba_lista_ver();
    prueba_lista_NULL();
    prueba_lista_volumen();
    prueba_lista_vacia_destruccion_con_free();
    prueba_lista_de_pilas_con_destruccion();
    prueba_lista_de_pilas_con_destruccion_manual();
    prueba_lista_iterar_interno();
    prueba_iterador_externo_operaciones_basicas();
    pruebas_iterador_externo_insertar();
    pruebas_iterador_externo_borrar();
    pruebas_iterador_externo_NULL();

}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif