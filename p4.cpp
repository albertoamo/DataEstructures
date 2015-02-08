/*
Autores: 

	Alberto Sánchez Amo 		NIA: 152871
	Luis Ángel Rodríguez Viñal 	NIA: 154186
	Alejandro Méndez Díaz		NIA: 163825

Asignatura: Estructuras de Datos y Algoritmos
*/

#include <stdio.h>
#include <string.h>
#include "tad_hash.cpp"

void printOpciones(){

	printf("\n****************************************************\n");
	printf("*              Menú Principal                      *\n");
	printf("****************************************************\n");
	printf("*                                                  *\n");
	printf("*     Escribe 0 para registrar nuevo coche         *\n");
	printf("*     Escribe 1 para registrar nuevo socio         *\n");
	printf("*     Escribe 2 para mostrar info coche            *\n");
	printf("*     Escribe 3 para registrar alquiler de coche   *\n");
	printf("*     Escribe 4 para registrar devolución de coche *\n"); 
	printf("*     Escribe 5 para mostrar info socio            *\n"); 
	printf("*     Escribe 6 para guardar en ficheros           *\n"); 
	printf("*     Escribe 7 para cargar de ficheros            *\n"); 
	printf("*     Escribe 8 para salir del programa            *\n"); 
	printf("*                                                  *\n");
	printf("****************************************************\n");
}

void saveRegfiles(Regfile **files, int i){

	FILE *registro = fopen("testeo.txt", "w");
	fprintf(registro,"Dni				Matricula	Fecha entrega	Fecha retorno	Fecha devuelto realmente\n");
	for(unsigned int x = 0; x < i; x++){
		fprintf(registro,"%s		%s		%s		%s		%s \n", files[x]->user,files[x]->id, files[x]->recDate, files[x]->retDate, files[x]->finDate);
	}

	fclose(registro);
}

void saveSocios(Hash* hash){

	FILE *registro = fopen("socios.txt", "w");
	fprintf(registro,"Dni				Appelidos			Nombre		Edad	Telefono\n");

	for(unsigned int x = 0; x < hash->size; x++){
		Nodo1 *auxiliar;
  		auxiliar = hash->listas[x]->begin;
		for(unsigned int y = 0; y < hash->listas[x]->size; y++){
			Socio *socio = (Socio*)auxiliar->valor;
			fprintf(registro,"%s		%s		%s		%d		%li \n", socio->dni, socio->surname, socio->name, *socio->age, *socio->phone);
			auxiliar = auxiliar->sigNodo;
		}
	}

	fclose(registro);
}

void saveCoches(Hash* hash){

	FILE *registro = fopen("fondos.txt", "w");
	fprintf(registro,"Matricula	Marca		Modelo	Color\n");

	for(unsigned int x = 0; x < hash->size; x++){
		Nodo1 *auxiliar;
  		auxiliar = hash->listas[x]->begin;
		for(unsigned int y = 0; y < hash->listas[x]->size; y++){
			Coche *coche = (Coche*)auxiliar->valor;
			fprintf(registro,"%s		%s		%s		%s \n", coche->id, coche->brand, coche->model, coche->color);
			auxiliar = auxiliar->sigNodo;
		}
	}

	fclose(registro);
}

//Registrar un nuevo coche
void opcionCero(Hash* hash){

	char null[1];

	char* id = (char*)malloc(30*sizeof(char));
	char* brand = (char*)malloc(30*sizeof(char));
	char* model = (char*)malloc(30*sizeof(char));
	char* color = (char*)malloc(30*sizeof(char));


	printf("Introduzca datos del nuevo coche a añadir\n");
	gets(null);//arregla el salto de linia

	printf("Introduzca matrícula:"); gets(id);

	printf("Introduzca marca:");  gets(brand);

	printf("Introduzca modelo:"); gets(model);

	printf("Introduzca color:");  gets(color);

	regCoche(hash,id,brand,model,color);

	printf("Se ha añadido el siguiente coche: %s %s %s %s", id, brand, model, color);
	
}

//Registrar nuevo socio
void opcionUno(Hash* hash){

	char null[1];
	gets(null);

	int* age = (int*)malloc(30*sizeof(int));
	long int *phone = (long int*)malloc(30*sizeof(long int));
	char* dni = (char*)malloc(30*sizeof(char));
	char* surname = (char*)malloc(30*sizeof(char));
	char* name = (char*)malloc(30*sizeof(char));

	printf("Introduzca datos del nuevo socio a añadir\n");

	printf("Introduzca DNI:"); gets(dni);

	printf("Introduzca apellidos:");  gets(surname);

	printf("Introduzca nombre:"); gets(name);

	printf("Introduzca edad:");  scanf("%d", age);

	printf("Introduzca telefono:");  scanf("%li", phone);

	regSocio(hash,dni,surname,name,age,phone);

	printf("Se ha añadido el siguiente socio: %s %s %s %d %li", dni, surname, name, *age, *phone);

	gets(null);

}

//Mostrar info coche
void opcionDos(Hash* hash){

	char null[1];
	gets(null);

	char matricula[20];

	printf("Introduzca matrícula del coche que quiere buscar:");  gets(matricula);

	//long int hashkey = strtoul (matricula, NULL, 0);
	printCoche(hash, (char*)matricula);

}

//Registrar alquiler vehículo
void opcionTres(Regfile** file, int i){

	char null[1];
	gets(null);

	char* matricula = (char*)malloc(30*sizeof(char));
	char* dni = (char*)malloc(30*sizeof(char));
	char* actual  = (char*)malloc(90*sizeof(char));
	char* fecha  = (char*)malloc(30*sizeof(char));

	printf("Introduzca matrícula del coche que quiere alquilar: ");
	gets(matricula);

	printf("Introduzca DNI del socio que alquilará el coche: ");
	gets(dni);

	printf("Introduzca fecha que quiere devolver el coche: ");
	gets(fecha);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	char* actual2  = (char*)malloc(90*sizeof(char));

	sprintf(actual, "%d/", tm.tm_mday);
	sprintf(actual2, "%d/", tm.tm_mon + 1);
	strcat(actual,actual2);
	sprintf(actual2, "%d", tm.tm_year + 1900);
	strcat(actual,actual2);

	file[i] = crearDev();
	file[i]->id = matricula;
	file[i]->user = dni;
	file[i]->recDate = actual;
	file[i]->retDate = fecha;

	free(actual2);
	
}

//Registrar devolución vehículo
void opcionCuatro(Regfile **file, int i){

	char null[1];
	gets(null);

	char* matricula = (char*)malloc(30*sizeof(char));
	char* dia = (char*)malloc(30*sizeof(char));

	printf("Introduzca matrícula del coche que se quiere devolver:");
	gets(matricula);

	printf("Introduzca matrícula el dia en el que se ha devuelto el coche:");
	gets(dia);

	for(unsigned int x = 0; x < i ; x++){
		if(file[x] != NULL){
			if(!strcmp(file[x]->id,matricula)){
				file[x]->finDate = dia;
				printf("Fecha introducida correctamente\n");
			}
		}
	}
	
	free(matricula);
	//free(dia);
}

//Mostrar info socio
void opcionCinco(Hash* hash){

	char null[1];
	gets(null);

	char dni[20];

	printf("Introduzca DNI del socio que quiere buscar:");  gets(dni);

	printSocio(hash,(char*) dni);
	
}

//Guardar en ficheros
void opcionSeis(Hash* fond, Hash* soc, Regfile** files, int i){

	char null[1];

	char resp[20];

	char si[] = "SI"; char no[] = "NO";

	gets(null);

	printf("¿Desea guardar los datos actuales en ficheros? Se sobreescribiran ficheros actuales (Escribe SI o NO):");
	gets(resp);

	if(strcmp(si,resp) == 0){

		//saveFiles(fond,soc,prest);
		printf("Los ficheros 'socios.txt', 'fondos.txt' y 'prestamos.txt' han sido guardados.");
		saveRegfiles(files,i);
		saveCoches(fond);
		saveSocios(soc);
	}
		
	
	if(strcmp(no,resp) == 0)
		printf("Operación abortada.");

	if(strcmp(si,resp) != 0 && strcmp(no,resp) != 0)
		printf("Por favor, escribe SI o NO como única respuesta\n");
	
}

//Cargar de ficheros
void opcionSiete(Hash* fondos, Hash* socios){

	char null[1];

	char resp[20];

	char si[] = "SI"; char no[] = "NO";

	gets(null);

	printf("¿Desea cargar ficheros? Se perderan todos los datos no guardados (Escribe SI o NO):");
	gets(resp);

	if(strcmp(si,resp) == 0){
		readSocios(socios);
		readFondos(fondos);
		printf("Los archivos 'socios.txt', 'fondos.txt' y 'prestamos.txt' han sido cargados.\n");
	}
		
	
	if(strcmp(no,resp) == 0)
		printf("Operación abortada.\n");

	if(strcmp(si,resp) != 0 && strcmp(no,resp) != 0)
		printf("Por favor, escribe SI o NO como única respuesta\n");

}

int main(){

	int option;

	//Creación de las tablas:
	int i = 0;
	Hash* socios = crearHash(7);
	Hash* fondos = crearHash(51);
	//Hash* prestamos = crearHash(7);
	Regfile** file = (Regfile**)malloc(20 * sizeof(Regfile*));

	while(1){

		printOpciones();
		printf("\nElegir Opción: ");
		scanf(" %d",&option);

		switch(option){

			case 0: opcionCero(fondos); break; //estructura feta
			case 1: opcionUno(socios); break; //estructura feta
			case 2: opcionDos(fondos); break;
			case 3: { opcionTres(file, i); i++;} break;
			case 4: opcionCuatro(file, i); break;
			case 5: opcionCinco(socios); break;
			case 6: opcionSeis(fondos, socios, file, i); break;
			case 7: opcionSiete(fondos, socios); break;
			case 8: 

				printf("Ejecución detenida por el usuario\n"); 

				if(socios)
					clearHashSocios(socios);

				if(fondos)
					clearHashCoches(fondos);
				if(file){

					for(unsigned int x = 0; x < i; x++){
						if(file[x]->id) free(file[x]->id);
						if(file[x]->user) free(file[x]->user);
						if(file[x]->recDate) free(file[x]->recDate);
						if(file[x]->retDate) free(file[x]->retDate);
						if(file[x]->finDate) free(file[x]->finDate);
					}
					free(file);
				}

				return 0; 
				break;

			default: printf("Opción no valida: elija un valor dentro de [0,8]\n");
		}

		printf("\nPresione [ENTER] para continuar:");
		getchar();

	}


	return 0;
}
