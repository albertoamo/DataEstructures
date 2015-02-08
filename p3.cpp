#include "p3_arbol.cpp"
#include "p3_lista.cpp"
#include <stdlib.h>

void chooseTad(){

	printf("\n*******************************************\n");
	printf("*              Menu Principal             *\n");
	printf("*******************************************\n");
	printf("*                                         *\n");
	printf("*   Escribe 0 para trabajar con listas    *\n");
	printf("*   Escribe 1 para trabajar con arboles   *\n");
	printf("*   Escribe 2 para tiempos listas         *\n");
	printf("*   Escribe 3 para tiempos arboles        *\n");
	printf("*   Escribe 4 para TERMINAR la ejecucion  *\n");
	printf("*                                         *\n");
	printf("*******************************************\n");

}

void chooseArbol(){

	printf("\n*******************************************\n");
	printf("*           INTERFAZ: Arboles             *\n");
	printf("*******************************************\n");
	printf("*                                         *\n");
	printf("*   Escribe 0 para crear un Arbol         *\n");
	printf("*   Escribe 1 para insertar un nodo       *\n");
	printf("*   Escribe 2 para borrar un nodo         *\n");
	printf("*   Escribe 3 para tiempo arbol aleatorio *\n");
	printf("*   Escribe 4 para imprimir arbol         *\n");
	printf("*   Escribe 5 para volver atras           *\n");
	printf("*   Escribe 6 para TERMINAR la ejecucion  *\n");
	printf("*                                         *\n");
	printf("*******************************************\n");
	
}

void chooseLista(){

	printf("\n*******************************************\n");
	printf("*           INTERFAZ: Listas              *\n");
	printf("*******************************************\n");
	printf("*                                         *\n");
	printf("*   Escribe 0 para crear una lista        *\n");
	printf("*   Escribe 1 para insertar un nodo       *\n");
	printf("*   Escribe 2 para borrar un nodo         *\n");
	printf("*   Escribe 3 para tiempo lista aleatoria *\n");
	printf("*   Escribe 4 para imprimir lista         *\n");
	printf("*   Escribe 5 para volver atras           *\n");
	printf("*   Escribe 6 para TERMINAR la ejecucion  *\n");
	printf("*                                         *\n");
	printf("*******************************************\n");
	
}

Arbol* arbolOpCero(Arbol *arbol){

	Arbol *newarbol = NULL;

	if(!arbol){
		newarbol = createTree(); 
		printf("\n->Un arbol vacio ha sido generado\n");
	}
	else{
		printf("\n->El arbol anterior ha sido eliminado\n");
		eliminarArbol(arbol);
		newarbol = createTree(); 
		printf("->Un arbol ha sido generado\n");

	}

	return newarbol;
}

void arbolOpUno(Arbol *arbol){

	if(!arbol){
		printf("->No existe ningun Arbol, crea un arbol antes, OPCION 1 !!!\n");
		return;
	}

	int dni;
	float sueldo;
	printf("\n->Introduzca datos del nodo [DNI Sueldo]: ");
	scanf("%d %f",&dni,&sueldo);
	insertNode(arbol,createUser(dni,sueldo));
	printf("\n->Nodo con DNI %d y Sueldo %f insertado.\n",dni,sueldo);
}

void arbolOpDos(Arbol *arbol){

	if(!arbol){
		printf("->No existe ningun Arbol, crea un arbol antes, OPCION 1 !!!\n");
		return;
	}

	int dni;
	printf("\n->Introduzca un DNI para borrar el nodo: ");
	scanf("%d",&dni);
	deleteNode(arbol,dni);
}

Arbol* arbolOpTres(Arbol *arbol){

	if(arbol)
		eliminarArbol(arbol);

	int size;
	//arbol = NULL;
	arbol = createTree(); 
	printf("\n->Introduzca un numero de nodos: ");
	scanf("%d",&size);
	float tiempo = tiempoArbol(arbol,size);
	printf("->El tiempo para %d nodos es de %f\n",size,tiempo);
	return arbol;

}

void arbolOpCuatro(Arbol *arbol){

	if(!arbol){
		printf("No existe ningun Arbol, crea un arbol antes, OPCION 1 !!!\n");
		return;
	}

	int type;
	printf("\n->Escriba 1 para inorden, 2 para posorden o 3 para preorden: ");
	scanf("%d",&type);
	printf("\n");
	printTree(arbol,type);

}

Lista* listaOpCero(Lista *lista){

	Lista *newlista = NULL;

	if(!lista){
		newlista = crearLista();
		printf("\n->Una lista vacia ha sido generada\n");
	}
	else{
		printf("\n->La lista anterior ha sido eliminado\n");
		eliminarLista(lista);
		newlista = crearLista(); 
		printf("->Una lista vacia ha sido generado\n");

	}

	return newlista;
}

void listaOpUno(Lista *lista){

	if(!lista){
		printf("->No existe ninguna lista, crea una lista antes, OPCION 1 !!!\n");
		return;
	}

	int dni;
	float sueldo;
	printf("\n->Introduzca datos del nodo [DNI Sueldo]: ");
	scanf("%d %f",&dni,&sueldo);
	insertarNuevoNodo(lista,createUser(dni,sueldo));
	printf("\n->Nodo con DNI %d y Sueldo %f insertado.\n",dni,sueldo);
}

void listaOpDos(Lista *lista){

	if(!lista){
		printf("->No existe ninguna Lista, crea una lista antes, OPCION 1 !!!\n");
		return;
	}

	int dni;
	printf("\n->Introduzca un DNI para borrar el nodo: ");
	scanf("%d",&dni);
	lista->actual = buscarElemento(lista,dni);
	if(lista->actual == NULL){
		printf("Nodo no encontrado\n");
		return;
	}
	else{
		//printf("\n\n%d\n\n",lista->actual->valor->dni);
		eliminarNodo(lista);
	}
}

Lista* listaOpTres(Lista *lista){

	if(lista != NULL)
		eliminarLista(lista);

	Lista *newlista = NULL;

	int size;
	newlista = crearLista(); 
	printf("\n->Introduzca un numero de nodos: ");
	scanf("%d",&size);
	float tiempo = tiempoLista(newlista,size);
	printf("->El tiempo para %d nodos es de %f\n",size,tiempo);
	return newlista;

}

void listaOpCuatro(Lista *lista){

	if(!lista){
		printf("No existe ninguna Lista, crea una Lista antes, OPCION 1 !!!\n");
		return;
	}

	recorrerLista(lista);

}

int opcionArbol(Arbol *arbol){

	int option;

	while(1){

		chooseArbol();
		printf("\nElegir Opcion: ");
		scanf("%d",&option);

		switch(option){
			case 0:{ arbol = arbolOpCero(arbol); } break;
			case 1:{ arbolOpUno(arbol); } break;
			case 2:{ arbolOpDos(arbol); } break;
			case 3:{ arbol = arbolOpTres(arbol); } break;
			case 4:{ arbolOpCuatro(arbol); } break;
			case 5:{ eliminarArbol(arbol); return 0; } break;
			case 6:{ eliminarArbol(arbol); exit(0); } break;
			default: printf("Opcion no valida: inserte un numero dentro del intervalo [0,5]\n"); break;
		}

		printf("\nPresione [ENTER] para continuar:");
		getchar();getchar();

	}

}

int opcionLista(Lista *lista){

	int option;

	while(1){

		chooseLista();
		printf("\nElegir Opcion: ");
		scanf("%d",&option);

		switch(option){
			case 0:{ lista = listaOpCero(lista); } break;
			case 1:{ listaOpUno(lista); } break;
			case 2:{ listaOpDos(lista); } break;
			case 3:{ lista = listaOpTres(lista); } break;
			case 4:{ listaOpCuatro(lista); } break;
			case 5:{ eliminarLista(lista); return 0; } break;
			case 6:{ eliminarLista(lista); exit(0); } break;
			default: printf("Opcion no valida: inserte un numero dentro del intervalo [0,5]\n"); break;
		}

		printf("\nPresione [ENTER] para continuar:");
		getchar();getchar();

	}

}

int ejercicioUno(){

	printf("\n*******************************************\n");
	printf("*        Calculo de tiempo: Listas        *\n");
	printf("*          [100,1000,10000,20000]         *\n");
	printf("*******************************************\n");

	Lista * lista1 = crearLista();
	Lista * lista2 = crearLista(); 
	Lista * lista3 = crearLista(); 
	Lista * lista4 = crearLista(); 

	float tiempo1 = tiempoLista(lista1,100);
	printf("\n-> Tiempo para 100 nodos: %f\n",tiempo1);
	float tiempo2 = tiempoLista(lista2,1000);
	printf("-> Tiempo para 1000 nodos: %f\n",tiempo2);
	float tiempo3 = tiempoLista(lista3,10000);
	printf("-> Tiempo para 10000 nodos: %f\n",tiempo3);
	float tiempo4 = tiempoLista(lista4,20000);
	printf("-> Tiempo para 20000 nodos: %f\n",tiempo4);

	eliminarLista(lista1);
	eliminarLista(lista2);
	eliminarLista(lista3);
	eliminarLista(lista4);

	printf("\nPresione [ENTER] para continuar:");
	getchar();getchar();

	return 0;

}

int ejercicioTres(){

	printf("\n*******************************************\n");
	printf("*        Calculo de tiempo: Arboles       *\n");
	printf("*          [100,1000,10000,20000]         *\n");
	printf("*******************************************\n");

	Arbol * arbol1 = createTree(); 
	Arbol * arbol2 = createTree(); 
	Arbol * arbol3 = createTree(); 
	Arbol * arbol4 = createTree(); 

	float tiempo1 = tiempoArbol(arbol1,100);
	printf("\n-> Tiempo para 100 nodos: %f\n",tiempo1);
	float tiempo2 = tiempoArbol(arbol2,1000);
	printf("-> Tiempo para 1000 nodos: %f\n",tiempo2);
	float tiempo3 = tiempoArbol(arbol3,10000);
	printf("-> Tiempo para 10000 nodos: %f\n",tiempo3);
	float tiempo4 = tiempoArbol(arbol4,20000);
	printf("-> Tiempo para 20000 nodos: %f\n",tiempo4);

	eliminarArbol(arbol1);
	eliminarArbol(arbol2);
	eliminarArbol(arbol3);
	eliminarArbol(arbol4);

	printf("\nPresione [ENTER] para continuar:");
	getchar();getchar();

	return 0;

}

int main(){

	int option;
	Lista *lista = NULL;
	Arbol *arbol = NULL;


	while(1){

		chooseTad();
		printf("\nElegir Opcion: ");
		scanf(" %d",&option);

		switch(option){
			case 0: opcionLista(lista); break;
			case 1: opcionArbol(arbol); break;
			case 2: ejercicioUno(); break;
			case 3: ejercicioTres(); break;
			case 4: return 0; break;
			default: printf("Opcion no valida: elija un valor dentro de [0,4]\n");
		}

	}

	//En caso de producirse un fallo, volvemos a 
	eliminarLista(lista);
	eliminarArbol(arbol);

	return 0;
}