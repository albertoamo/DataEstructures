/*
Autores: 

	Alberto Sánchez Amo 		NIA: 152871
	Luis Ángel Rodríguez Viñal 	NIA: 154186
	Alejandro Méndez Díaz		NIA: 163825

Asignatura: Estructuras de Datos y Algoritmos
*/

//--Librerías--//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include "utils.h"

//--buscarNodo: Pasamos como parámetro una lista y el nodo que queremos buscar en dicha lista. Devuelve el nodo que buscamos en la lista--//
Nodo* buscarNodo(Lista *lista,Nodo *node){

  	Nodo *auxiliar;
  	auxiliar = lista->begin;

	for(unsigned int x = 0; x < lista->size; x++){
		if(auxiliar->sigNodo == node)
			return auxiliar;
		else
			auxiliar = auxiliar->sigNodo;
	}

}

//Algoritmo de burbuja, lo utilizamos para ordenar el numero de dnis en forma creciente.
void bubbleSort(Lista *lista)
{
 
 	for (unsigned int x=0; x < lista->size - 1; x++){
  		Nodo *auxiliar = lista->begin;  
		for (unsigned int i=0; i < lista->size - 1; i++){
        	if (auxiliar->valor->dni > auxiliar->sigNodo->valor->dni){
            	int temp = auxiliar->valor->dni;
            	auxiliar->valor->dni = auxiliar->sigNodo->valor->dni;
            	auxiliar->sigNodo->valor->dni = temp;
        	}
          	auxiliar = auxiliar->sigNodo;
        }
	}
	
}

//--createUser: Reservarmos memoria para un nodo, que en este caso corresponde a un estudiante--//
User* createUser(int dni, int edad, float nota){

	User *user = (User*)malloc(sizeof(User));
	user->dni = dni;
	user->edad = edad;
	user->nota = nota;
	return user;
}

//--crearLista: Creamos una lista vacía por defecto--//
Lista* crearLista(){

	Lista *lista = (Lista*)malloc(sizeof(Lista));

	lista->size = 0;
	lista->begin = NULL;
	lista->actual = NULL;

	return lista;
}

//--listaVacía: Devuelve un booleano true si la lista está vacía--// 
bool listaVacia(Lista *lista){

	if(lista->begin != NULL)
		return false;
	else
		return true;
}

//--modificarElemento: Modificamos la nota de un nodo--//
void modificarElemento(Nodo *nodo, float nota){

	nodo->valor->nota = nota;

	//Si quisiéramos modificar otros valores del nodo, deberíamos pasar más argumentos y asignarlos de la siguiente manera:
	//nodo->valor->dni = data->dni;
	//nodo->valor->edad = data->edad;
}

//--insertarNuevoNodo: añadimos un nodo estudiante a la lista--//
void insertarNuevoNodo(Lista *lista,User *data){

	Nodo *nodo = (Nodo*)malloc(sizeof(Nodo));

	//Miramos que si no hay un principio, este sea el nuevo begin
	if(lista->begin == NULL || lista->actual == NULL){
		lista->ghost = (Nodo*)malloc(sizeof(Nodo));
		nodo->valor = data;
		lista->begin = nodo;
		lista->end = nodo;
		lista->actual = nodo;
		nodo->sigNodo = lista->ghost;
		lista->size++;
		return;
	}
	if(lista->actual == lista->end)
		lista->end = nodo;

	if(lista->actual == lista->ghost){
		lista->ghost->sigNodo = nodo;
		lista->ghost->valor = data;
		lista->end = lista->ghost;
		lista->ghost = nodo;
		lista->actual = lista->ghost;
		lista->size++;
		return;
	}
	
	//De esta manera se situan en la lista de derecha a izquierda

	nodo->sigNodo = lista->actual->sigNodo;
	lista->actual->sigNodo = nodo;
	nodo->valor = lista->actual->valor;
	lista->actual->valor = data;

	lista->size++;
	bubbleSort(lista);
	
}

//--eliminarNodo: elimina el nodo actual de una lista--//
void eliminarNodo(Lista *lista){

	//Comprueba si la lista está vacía
	if(listaVacia(lista)){
		printf("\nEsta lista está vacía\n");
		return;
	}

	//Nodo auxiliar
	Nodo *node;

	//Si el nodo actual es el principio
	if(lista->actual == lista->begin){
		lista->begin = lista->actual->sigNodo;	//el nodo begin ahora será el siguiente
		node = lista->begin;
	}
	else if(lista->actual != lista->begin && lista->actual != lista->end){ //o si el nodo actual se encuentra en medio la lista
		node = buscarNodo(lista,lista->actual);
		node->sigNodo = lista->actual->sigNodo;
	}

	if(lista->actual == lista->end){//o si el actual es el final
		lista->end = buscarNodo(lista,lista->end);
		node = lista->end;
	}

	//Liberamos memoria auxiliar
	free(lista->actual->valor);
	free(lista->actual);
	lista->actual = node; //refrescamos el nodo actual
	
	//El tamaño de la lista disminuye 1 valor
	lista->size--;
}

//--primerElemento: Dada una lista, devuelve el nodo inicial--//
Nodo *primerElemento(Lista *lista){

	return lista->begin;
}

//--ultimoElemento: Dada una lista, devuelve el nodo final--//
Nodo* ultimoElemento(Lista *lista){

	return lista->end;
}

//--recorrerLista: Printeamos por pantalla todo el contenido de una lista--//
void recorrerLista(Lista *lista){

	if(listaVacia(lista)){
		printf("Esta lista está vacía\n");
		return;
	}

  	Nodo *auxiliar;
  	auxiliar = lista->begin;

  	for(unsigned int x = 0; x < lista->size; x++){
  		printf("******** Nodo %d ********\n\n",x);
     	printf("  DNI: %d\n  Edad: %d\n  PromedioCalif: %f\n\n", 
     		auxiliar->valor->dni,auxiliar->valor->edad,auxiliar->valor->nota);
     	printf("------------------------\n");
      	auxiliar = auxiliar->sigNodo;
  	}
}

//--imprimirNodo: imprimimos por pantalla los valores de un nodo--//
void imprimirNodo(Lista *lista){

  	Nodo *auxiliar;
  	auxiliar = lista->begin;

	for(unsigned int x = 0; x < lista->size; x++){
		if(auxiliar->valor->dni == lista->actual->valor->dni){
			printf("******** Nodo %d ********\n\n",x);
     		printf("  DNI: %d\n  Edad: %d\n  PromedioCalif: %f\n\n", 
     				auxiliar->valor->dni,auxiliar->valor->edad,auxiliar->valor->nota);
     		printf("------------------------\n");
		}
		auxiliar = auxiliar->sigNodo;
	}

}

//--buscarElemento: buscamos un valor de un nodo que se encuentra dentro de la lista y lo devolvemos--//
Nodo* buscarElemento(Lista *lista, int data){


  	Nodo *auxiliar;
  	auxiliar = lista->begin;

	for(unsigned int x = 0; x < lista->size; x++){
		if(auxiliar->valor->dni == data)
			return auxiliar;
		else
			auxiliar = auxiliar->sigNodo;
	}

}

//eliminarLista: Liberamos memoria para cada nodo de la lista
void eliminarLista(Lista *lista){

	Nodo *auxiliar;
  	Nodo *iterator;
  	iterator = lista->begin;

	for(unsigned int x = 0; x < lista->size; x++){
		auxiliar = iterator;
		iterator = iterator->sigNodo;
		free(auxiliar->valor);
		free(auxiliar);
	}

	free(lista->ghost);
	free(lista);

}

//--Main principal del código--//
int main(){

	//Creamos una lista
	Lista *lista = crearLista();

	//Añadimos un conjunto de estudiantes, con su DNI, su edad y su nota correspondiente
	insertarNuevoNodo(lista,createUser(3, 20, 5.1));
	insertarNuevoNodo(lista,createUser(1, 16, 6.7));
	insertarNuevoNodo(lista,createUser(5, 14, 3.4));
	insertarNuevoNodo(lista,createUser(6, 15, 8.2));
	insertarNuevoNodo(lista,createUser(2, 17, 9.3));
	insertarNuevoNodo(lista,createUser(4, 26, 8.9));

	//Mostramos la lista entera por defecto y ordenada
	printf("-----Lista inicial: Nodos iniciales ordenados:-----\n\n");
	recorrerLista(lista);
	
	//Parte 1: Buscamos un estudiante concreto y imprimimos su información
	printf("-----Parte 1: Buscamos el estudiante con DNI 4:-----\n\n");
	lista->actual = buscarElemento(lista,4);
	imprimirNodo(lista);

	//Parte 2: Eliminamos el último elemento de la lista
	lista->actual = lista->end;
	eliminarNodo(lista);
	printf("\n\n-----Parte 2: Lista de nodos actualizada (ultimo elemento eliminado):-----\n\n");
	recorrerLista(lista);

	//Parte 3: Modificamos el valor de dos estudiantes (el 2 y el 3 por ejemplo)
	//Buscamos los del DNI 2 y 3, y le cambiamos la nota:
	modificarElemento(buscarElemento(lista,2),7.1);
	modificarElemento(buscarElemento(lista,3),4.99);
	printf("\n\n-----Parte 3: Lista de nodos actualizada (elementos 2 y 3 modificados):-----\n\n");
	recorrerLista(lista);

	//Finalmente liberamos memoria
	eliminarLista(lista);
	return 0;
}
